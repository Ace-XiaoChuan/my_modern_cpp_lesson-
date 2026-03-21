#include <memory>
#include <cmath>
#include <thread>
#include <atomic>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "std_msgs/msg/int32.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"

#include "robot_interfaces/srv/get_robot_status.hpp"
#include "robot_interfaces/action/navigation.hpp"

class TaskManagerNode : public rclcpp::Node
{
public:
    // ======================== 类型别名 ========================
    using Navigation = robot_interfaces::action::Navigation;
    using GoalHandle = rclcpp_action::ServerGoalHandle<Navigation>;
    using GetRobotStatus = robot_interfaces::srv::GetRobotStatus;

    // ======================== 构造函数 ========================
    TaskManagerNode() : Node("task_manager_node")
    {
        init_subscribers();
        init_service();
        init_action_server();
        RCLCPP_INFO(this->get_logger(), "TaskManagerNode 已启动");
    }

private:
    // ======================== 成员变量 ========================
    // --- 状态数据（多线程访问，使用 atomic） ---
    std::atomic<int> current_battery_{0};
    std::atomic<bool> is_in_task_{false};

    // --- 位置数据（订阅回调 + execute 线程共享，需注意同步） ---
    geometry_msgs::msg::Point current_position_;
    std::mutex position_mutex_;

    // --- ROS 通信接口 ---
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr battery_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PointStamped>::SharedPtr pose_sub_;
    rclcpp::Service<GetRobotStatus>::SharedPtr service_;
    rclcpp_action::Server<Navigation>::SharedPtr action_server_;

    // ======================== 初始化函数 ========================
    void init_subscribers()
    {
        battery_sub_ = this->create_subscription<std_msgs::msg::Int32>(
            "battery_level", 10,
            [this](const std_msgs::msg::Int32::SharedPtr msg)
            {
                on_battery_received(msg);
            });

        pose_sub_ = this->create_subscription<geometry_msgs::msg::PointStamped>(
            "robot_pose", 10,
            [this](const geometry_msgs::msg::PointStamped::SharedPtr msg)
            {
                on_pose_received(msg);
            });
    }

    void init_service()
    {
        service_ = this->create_service<GetRobotStatus>(
            "get_robot_status",
            [this](const GetRobotStatus::Request::SharedPtr request,
                   GetRobotStatus::Response::SharedPtr response)
            {
                on_get_robot_status(request, response);
            });
    }

    void init_action_server()
    {
        action_server_ = rclcpp_action::create_server<Navigation>(
            this, "navigation",
            // 目标请求回调
            [this](const rclcpp_action::GoalUUID &uuid,
                   std::shared_ptr<const Navigation::Goal> goal)
            {
                return on_goal_request(uuid, goal);
            },
            // 取消请求回调
            [this](const std::shared_ptr<GoalHandle> goal_handle)
            {
                return on_cancel_request(goal_handle);
            },
            // 目标接受回调
            [this](const std::shared_ptr<GoalHandle> goal_handle)
            {
                on_goal_accepted(goal_handle);
            });
    }

    // ================ 订阅回调 ================
    void on_battery_received(const std_msgs::msg::Int32::SharedPtr msg)
    {
        current_battery_ = msg->data;
        RCLCPP_INFO(this->get_logger(), "当前电量: %d%%", current_battery_.load());
    }

    void on_pose_received(const geometry_msgs::msg::PointStamped::SharedPtr msg)
    {
        std::lock_guard<std::mutex> lock(position_mutex_);
        current_position_ = msg->point;
        RCLCPP_INFO(this->get_logger(), "当前位置: (%.1f, %.1f, %.1f)",
                    current_position_.x, current_position_.y, current_position_.z);
    }

    // ================ 服务回调 ================
    void on_get_robot_status(
        const GetRobotStatus::Request::SharedPtr /*request*/,
        GetRobotStatus::Response::SharedPtr response)
    {
        std::lock_guard<std::mutex> lock(position_mutex_);
        response->battery_level = current_battery_;
        response->x = current_position_.x;
        response->y = current_position_.y;
        response->z = current_position_.z;
        response->has_task = is_in_task_;
    }

    // ================ 动作回调 ================
    /// 判断是否接受目标
    rclcpp_action::GoalResponse on_goal_request(
        const rclcpp_action::GoalUUID & /*uuid*/,
        std::shared_ptr<const Navigation::Goal> goal)
    {
        RCLCPP_INFO(this->get_logger(),
                    "收到导航请求 -> 目标: (%.1f, %.1f)", goal->target_x, goal->target_y);

        if (is_in_task_)
        {
            RCLCPP_WARN(this->get_logger(), "当前有任务执行中，拒绝新目标");
            return rclcpp_action::GoalResponse::REJECT;
        }
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    /// 处理取消请求
    rclcpp_action::CancelResponse on_cancel_request(
        const std::shared_ptr<GoalHandle> /*goal_handle*/)
    {
        RCLCPP_INFO(this->get_logger(), "收到取消请求，允许取消");
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    /// 目标被接受后，启动异步执行线程
    void on_goal_accepted(const std::shared_ptr<GoalHandle> goal_handle)
    {
        std::thread([this, goal_handle]()
                    { execute_navigation(goal_handle); })
            .detach();
    }

    // ================ 导航执行逻辑 ================
    void execute_navigation(const std::shared_ptr<GoalHandle> goal_handle)
    {
        RCLCPP_INFO(this->get_logger(), "===== 开始执行导航任务 =====");
        is_in_task_ = true;

        const auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared<Navigation::Feedback>();
        auto result = std::make_shared<Navigation::Result>();
        rclcpp::Rate loop_rate(1); // 1 Hz

        const double target_x = goal->target_x;
        const double target_y = goal->target_y;
        constexpr double ARRIVAL_TOLERANCE = 0.1; // 到达容差 (米)

        while (rclcpp::ok())
        {
            // --- 检查取消 ---
            if (goal_handle->is_canceling())
            {
                result->success = false;
                result->message = "导航任务被主动取消";
                goal_handle->canceled(result);
                RCLCPP_WARN(this->get_logger(), "任务已取消");
                is_in_task_ = false;
                return;
            }

            // --- 计算剩余距离 ---
            double cur_x, cur_y;
            {
                std::lock_guard<std::mutex> lock(position_mutex_);
                cur_x = current_position_.x;
                cur_y = current_position_.y;
            }

            double dx = target_x - cur_x;
            double dy = target_y - cur_y;
            double distance = std::sqrt(dx * dx + dy * dy);

            // --- 判断是否到达 ---
            if (distance < ARRIVAL_TOLERANCE)
            {
                break;
            }

            // --- 发布反馈 ---
            feedback->current_x = cur_x;
            feedback->current_y = cur_y;
            feedback->distance_remaining = distance;
            goal_handle->publish_feedback(feedback);
            RCLCPP_INFO(this->get_logger(), "导航中... 剩余距离: %.2f m", distance);

            loop_rate.sleep();
        }

        // --- 任务完成 ---
        if (rclcpp::ok())
        {
            result->success = true;
            result->message = "成功到达目标点";
            goal_handle->succeed(result);
            RCLCPP_INFO(this->get_logger(), "===== 导航任务完成 =====");
        }
        is_in_task_ = false;
    }
};

// ======================== 主函数 ========================
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TaskManagerNode>());
    rclcpp::shutdown();
    return 0;
}