#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
    public:
        MinimalSubscriber()
        : Node("minimal_subscriber")
        {
            subscription_ = this->create_subscription<turtlesim::msg::Pose>(
                "/turtle1/pose",
                10,
                std::bind(&MinimalSubscriber::topic_callback, this, _1));
        }

    private:
        void topic_callback(const std::shared_ptr<turtlesim::msg::Pose> msg)
        {
            RCLCPP_INFO(this->get_logger(), "%f", msg->x);
        }
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}