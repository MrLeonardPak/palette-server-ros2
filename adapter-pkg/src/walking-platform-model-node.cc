#include "adapter-pkg/walking-platform-model-node.hh"
#include "extra-constants.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

WalkingPlatformModelNode::WalkingPlatformModelNode(std::string_view node_name,
                                                   std::string_view topic_name,
                                                   dto::Region workzone)
    : Node(node_name.data()), workzone_(workzone) {
  publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
      topic_name.data(), extra_const::kQos);
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
  RCLCPP_INFO(this->get_logger(), "Set speed X: '%d'", msg.linear.x);
}

void WalkingPlatformModelNode::SetSpeedX(float speed) {
  auto msg = geometry_msgs::msg::Twist();
  msg.angular.z = 0.0;
  msg.linear.x = speed;
  publisher_->publish(msg);
  RCLCPP_INFO(this->get_logger(), "Set speed X: '%d'", msg.linear.x);
}

void WalkingPlatformModelNode::SetSpeedY(float speed) {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Set speed Y: '%d'", speed);
}

dto::Region WalkingPlatformModelNode::get_workzone() const {
  return workzone_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg