#include "adapter-pkg/walking-platform-model-node.hh"

#include <chrono>
#include <functional>

using namespace std::chrono_literals;

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

WalkingPlatformModelNode::WalkingPlatformModelNode(std::string node_name,
                                                   std::string topic_name,
                                                   dto::Region workzone)
    : IPlatformNode(std::move(node_name)), workzone_(workzone) {
  publisher_ =
      create_publisher<geometry_msgs::msg::Twist>(std::move(topic_name), 10);
}

void WalkingPlatformModelNode::ShiftY(float shift) {
  // TODO отправить сообщение в топик для управления платформой
  RCLCPP_INFO(get_logger(), "Set platform shift: %.2f", shift);
}

void WalkingPlatformModelNode::ShiftX(float shift) {
  ShiftY(shift);
  RCLCPP_WARN(get_logger(), "Don`t use WalkingPlatformModelNode::ShiftX!");
}

// HACK: Метод Rotate должен принимать угол, а не скорость
void WalkingPlatformModelNode::Rotate(float angle) {
  // TODO отправить сообщение в топик для управления платформой
  RCLCPP_INFO(get_logger(), "Rotate platform on: %.2f", angle);
}

void WalkingPlatformModelNode::set_y_speed(float speed) {
  linear_speed_ = speed;
  RCLCPP_INFO(get_logger(), "Set platform linear speed: %.2f", speed);
}

void WalkingPlatformModelNode::set_x_speed(float speed) {
  RCLCPP_WARN(get_logger(), "Don`t use WalkingPlatformModelNode::SetSpeedX!");
  set_y_speed(speed);
}

void WalkingPlatformModelNode::set_angular_speed(float speed) {
  angular_speed_ = speed;
  RCLCPP_INFO(get_logger(), "Set platform angular speed: %.2f", speed);
}

dto::Region WalkingPlatformModelNode::get_workzone() const {
  return workzone_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg