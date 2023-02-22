#include "adapter-pkg/walking-platform-model-node.hh"
#include <functional>

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

WalkingPlatformModelNode::WalkingPlatformModelNode(
    std::string const& node_name,
    std::string const& linear_topic_name,
    std::string const& rotate_topic_name,
    dto::props::Platform props)
    : node_(rclcpp::Node::make_shared(node_name)), props_(props) {
  linear_publisher_ = node_->create_publisher<platform_msg::msg::CmdLinear>(
      std::move(linear_topic_name), 10);
  rotate_publisher_ = node_->create_publisher<platform_msg::msg::CmdRot>(
      std::move(rotate_topic_name), 10);
}

void WalkingPlatformModelNode::ShiftY(float shift) {
  // TODO отправить сообщение в топик для управления платформой
  auto message = platform_msg::msg::CmdLinear();
  // FIXME убрать ограничение
  message.step = std::min(shift, 0.35f);
  message.vel = std::min(linear_speed_, 0.15f);
  linear_publisher_->publish(message);
  RCLCPP_INFO(node_->get_logger(), "Set platform shift: %.2f", shift);
}

void WalkingPlatformModelNode::ShiftX(float shift) {
  ShiftY(shift);
  RCLCPP_WARN(node_->get_logger(),
              "Don`t use WalkingPlatformModelNode::ShiftX!");
}

// HACK: Метод Rotate должен принимать угол, а не скорость
void WalkingPlatformModelNode::Rotate(float angle) {
  auto message = platform_msg::msg::CmdRot();
  message.vel = std::min(angular_speed_, 0.15f);
  message.step = angle;
  rotate_publisher_->publish(message);
  // TODO отправить сообщение в топик для управления платформой
  RCLCPP_INFO(node_->get_logger(), "Rotate platform on: %.2f", angle);
}

void WalkingPlatformModelNode::set_y_vel(float speed) {
  linear_speed_ = speed;
  RCLCPP_INFO(node_->get_logger(), "Set platform linear speed: %.2f", speed);
}

void WalkingPlatformModelNode::set_x_vel(float speed) {
  RCLCPP_WARN(node_->get_logger(),
              "Don`t use WalkingPlatformModelNode::SetSpeedX!");
  set_y_vel(speed);
}

void WalkingPlatformModelNode::set_ang_vel(float speed) {
  angular_speed_ = speed;
  RCLCPP_INFO(node_->get_logger(), "Set platform angular speed: %.2f", speed);
}

dto::props::Platform WalkingPlatformModelNode::get_props() const {
  return props_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg
