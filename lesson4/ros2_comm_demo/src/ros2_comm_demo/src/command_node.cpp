#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "robot_interfaces/srv/get_robot_status.hpp"
#include "robot_interfaces/action/navigation.hpp"

using namespace std::chrono_literals;

class CommandNode : public rclcpp::Node
{
public:
    using Navigation = robot_interfaces::action::Navigation;
    using GoalHandleNavigation = rclcpp_action::ClientGoalHandle<Navigation>;

    CommandNode() : Node("command")
    {
        // ========== 1. 订阅电量 ==========
        subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "battery_level", 10,
            [this](std_msgs::msg::Int32::SharedPtr msg)
            { current_battery_ = msg->data; });

        // ========== 2. 服务客户端 ==========
        service_client_ = this->create_client<robot_interfaces::srv::GetRobotStatus>(
            "get_robot_status");
        service_timer_ = this->create_wall_timer(
            3s, [this]()
            { send_request(); });

        // ========== 3. 动作客户端 ==========
        action_client_ = rclcpp_action::create_client<Navigation>(
            this, "Navigation");

        // 只发送一次目标，所以用一个一次性定时器
        // 等 2 秒后发送目标（给服务端启动的时间）
        action_timer_ = this->create_wall_timer(
            2s, [this]()
            { send_goal(); });
    }

private:
    // ========== 成员变量 ==========
    int current_battery_ = 0;
    bool goal_sent_ = false; // 防止重复发送

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
    rclcpp::Client<robot_interfaces::srv::GetRobotStatus>::SharedPtr service_client_;
    rclcpp::TimerBase::SharedPtr service_timer_;

    rclcpp_action::Client<Navigation>::SharedPtr action_client_; 
    rclcpp::TimerBase::SharedPtr action_timer_;


    void send_request()
    {
        if (!service_client_->wait_for_service(1s))
        {
            RCLCPP_WARN(this->get_logger(), "等待服务上线...");
            return;
        }
        auto request = std::make_shared<robot_interfaces::srv::GetRobotStatus::Request>();
        service_client_->async_send_request(request,
                                            [this](rclcpp::Client<robot_interfaces::srv::GetRobotStatus>::SharedFuture future)
                                            {
                                                auto response = future.get();
                                                RCLCPP_INFO(this->get_logger(),
                                                            "【状态】电量:%d 位置:(%.1f,%.1f,%.1f) 任务:%s",
                                                            response->battery_level,
                                                            response->x, response->y, response->z,
                                                            response->has_task ? "是" : "否");
                                            });
    }

    //  Action 相关

    // ---------- 第①步：发送目标 ----------
    void send_goal()
    {
        // 只发送一次，之后取消定时器
        action_timer_->cancel();

        if (goal_sent_)
            return;

        // 检查动作服务器是否在线
        if (!action_client_->wait_for_action_server(3s))
        {
            RCLCPP_ERROR(this->get_logger(), "动作服务器不在线！");
            return;
        }

        // --- 组装目标 ---
        auto goal_msg = Navigation::Goal();
        goal_msg.target_x = 5.0; // 目标 x
        goal_msg.target_y = 3.0; // 目标 y
        RCLCPP_INFO(this->get_logger(), "发送导航目标: (%.1f, %.1f)",
                    goal_msg.target_x, goal_msg.target_y);

        // --- 配置发送选项（绑定三个回调）---
        auto send_goal_options =
            rclcpp_action::Client<Navigation>::SendGoalOptions();

        // 回调1: 服务端是否接受目标
        send_goal_options.goal_response_callback =
            [this](const GoalHandleNavigation::SharedPtr &goal_handle)
        {
            goal_response_callback(goal_handle);
        };

        // 回调2: 收到反馈
        send_goal_options.feedback_callback =
            [this](GoalHandleNavigation::SharedPtr,
                   const std::shared_ptr<const Navigation::Feedback> feedback)
        {
            feedback_callback(feedback);
        };

        // 回调3: 收到最终结果
        send_goal_options.result_callback =
            [this](const GoalHandleNavigation::WrappedResult &result)
        {
            result_callback(result);
        };

        // --- 异步发送！---
        action_client_->async_send_goal(goal_msg, send_goal_options);
        goal_sent_ = true;
    }

    // ---------- 第②步：目标响应回调 ----------
    // 服务端告诉你："我接受/拒绝了你的目标"
    void goal_response_callback(const GoalHandleNavigation::SharedPtr &goal_handle)
    {
        if (!goal_handle)
        {
            RCLCPP_ERROR(this->get_logger(), "❌ 目标被服务端拒绝！");
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "✅ 目标被接受，等待执行...");
        }
    }

    // ---------- 第③步：反馈回调 ----------
    // 服务端在执行过程中不断发来进度
    void feedback_callback(const std::shared_ptr<const Navigation::Feedback> feedback)
    {
        RCLCPP_INFO(this->get_logger(),
                    "📡 反馈 -> 当前位置: (%.2f, %.2f), 剩余距离: %.2f",
                    feedback->current_x,
                    feedback->current_y,
                    feedback->distance_remaining);
    }

    // ---------- 第④步：结果回调 ----------
    // 任务最终完成（成功/失败/取消）
    void result_callback(const GoalHandleNavigation::WrappedResult &result)
    {
        switch (result.code)
        {
        case rclcpp_action::ResultCode::SUCCEEDED:
            RCLCPP_INFO(this->get_logger(), "🎉 导航成功！消息: %s",
                        result.result->message.c_str());
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(), "💥 导航被中止！消息: %s",
                         result.result->message.c_str());
            break;
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_WARN(this->get_logger(), "⚠️  导航被取消！消息: %s",
                        result.result->message.c_str());
            break;
        default:
            RCLCPP_ERROR(this->get_logger(), "未知结果");
            break;
        }
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CommandNode>());
    rclcpp::shutdown();
    return 0;
}