#include <chrono>
#include "lesson5_composition/talker.hpp"

namespace learn_compose
{
    using namespace std::chrono_literals;
    Talker::Talker(const rclcpp::NodeOptions &options) : Node("talker", options)
    {
        pub_ = this->create_publisher<std_msgs::msg::Int32>("count", 10);
        auto callback = [&]() -> void
        {
            std::unique_ptr<std_msgs::msg::Int32> msg = std::make_unique<std_msgs::msg::Int32>();
            msg->data = count_++;
            RCLCPP_INFO(this->get_logger(), "发布数据：%d(0x%1lX)", msg->data, reinterpret_cast<std::uintptr_t>(msg.get()));
            // int a = 5;
            // 5 是右值（临时值）
            // std::move(msg) 是右值
            // std::move(msg) 之前：
            // msg 栈地址 : 0x1000 → 指向堆 : 0x5000(Int32对象)

            // std::move(msg) 之后：
            // 原 msg 栈地址 : 0x1000 → nullptr（所有权已转移）
            // 发布者内部 : → 堆 : 0x5000(Int32对象)  ← 现在发布者负责

            // 回调函数结束：
            // msg 变量销毁（已是 nullptr，无需释放）
            // 堆上对象什么时候销毁？取决于发布者的逻辑
            pub_->publish(std::move(msg));
        };
        timer_ = this->create_wall_timer(1s, callback);
    }

}