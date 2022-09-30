#include "adapter-pkg/walking-platform-model-node.hh"

#include <chrono>
#include <functional>

#include "extra-constants.hh"

using namespace std::chrono_literals;

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

WalkingPlatformModelNode::WalkingPlatformModelNode(std::string_view node_name,
                                                   std::string_view topic_name,
                                                   dto::Region workzone)
    : Node(node_name.data()), workzone_(workzone) {
  publisher_ =
      this->create_publisher<geometry_msgs::msg::Twist>(topic_name.data(), 10);
}

void WalkingPlatformModelNode::ShiftX(float shift) {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Set shift X: '%d'", shift);
}

void WalkingPlatformModelNode::ShiftY(float shift) {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Set shift Y: '%d'", shift);
}

// HACK: Метод Rotate должен принимать угол, а не скорость
void WalkingPlatformModelNode::Rotate(float speed) {
  auto msg = geometry_msgs::msg::Twist();
  msg.angular.set__x(0.0).set__z(speed);
  publisher_->publish(msg);
  RCLCPP_INFO(this->get_logger(), "Set speed Z: '%f'", msg.linear.x);
}

void WalkingPlatformModelNode::SetSpeedX(float speed) {
  auto msg = geometry_msgs::msg::Twist();
  // auto tmp = geometry_msgs::msg::Vector3();
  // tmp.set__x(speed).set__y(speed).set__z(speed);
  // msg.set__linear(tmp);
  msg.linear.set__x(speed);
  publisher_->publish(msg);
  RCLCPP_INFO(this->get_logger(), "Set speed X: '%f'", msg.linear.x);
}

void WalkingPlatformModelNode::SetSpeedY(float speed) {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Set speed Y: '%d'", speed);
}

dto::Region WalkingPlatformModelNode::get_workzone() const {
  return workzone_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg