#include <memory>
#include <chrono>
#include <functional>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;


class TurtleController: public rclcpp::Node
{
    public:
      TurtleController()
      : Node("turtle_controller")
       {
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
            subscription_ = this->create_subscription<turtlesim::msg::Pose>(
                "/turtle1/pose",
                10,
                 std::bind(&TurtleController::callback, this, _1));
        }
    
    private:
        void callback(const std::shared_ptr<turtlesim::msg::Pose> pose)
        {
            auto cmd = geometry_msgs::msg::Twist();
            if ((pose->x > 9.0) or (pose->x < 2.0) or (pose->y > 9.0) or (pose->y < 2.0)){
                cmd.linear.x = 1.0;
                cmd.angular.z = 0.9;
            }
            else {
                cmd.linear.x = 5.0;
                cmd.angular.z = 0.0;
            }
            publisher_->publish(cmd);
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtleController>());
  rclcpp::shutdown();
  return 0;
}