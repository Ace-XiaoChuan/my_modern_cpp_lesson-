#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class BatteryNode : public rclcpp::Node
{
public:
    BatteryNode() : Node("battery_node")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("battery_talker", 10);
        timer_ = this->create_wall_timer(1000ms, [this]()
                                         { timer_callback(); });
    }

private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "当前电量为42%";
        publisher_->publish(message);
    }
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BatteryNode>());
    rclcpp::shutdown();
    return 0;
}