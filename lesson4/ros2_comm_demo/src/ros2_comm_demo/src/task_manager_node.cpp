#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"

class TaskManagerNode : public rclcpp::Node
{
public:
    TaskManagerNode() : Node("task_manager_node")
    {
        // 初始化电池订阅器
        battery_sub_ = this->create_subscription<std_msgs::msg::Int32>("battery_level", 10, [this](const std_msgs::msg::Int32::SharedPtr msg)
                                                                       { battery_callback(msg); });
        // 初始化位置订阅器
        pose_sub_ = this->create_subscription<geometry_msgs::msg::PointStamped>("robot_position", 10, [this](const geometry_msgs::msg::PointStamped::SharedPtr pose)
                                                                                { pose_callback(pose); });
    }

private:
    // ---声明成员变量---
    int current_battery_ = 0;
    geometry_msgs::msg::Point point_;
    // ---声明成员函数---
    // 声明电池回调函数
    void battery_callback(const std_msgs::msg::Int32::SharedPtr msg)
    {
        current_battery_ = msg->data;
        RCLCPP_INFO(this->get_logger(), "当前电量为：%d", current_battery_);
    };
    // 声明位置回调函数
    void pose_callback(const geometry_msgs::msg::PointStamped pose)
    {
        point_.x = pose.point.x;
        point_.y = pose.point.y;
        point_.z = pose.point.z;
        RCLCPP_INFO(this->get_logger(), "当前位置为：%.1f,%.1f,%.1f", point_.x, point_.y, point_.z);
    };

    // ---声明订阅器---
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr battery_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PointStamped>::SharedPtr pose_sub_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TaskManagerNode>());
    rclcpp::shutdown();
    return 0;
}