#include "adapter-pkg/walking-platform-model-node.hh"

#include <chrono>
#include <functional>

using namespace std::chrono_literals;

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

WalkingPlatformModelNode::WalkingPlatformModelNode(std::string_view node_name,
                                                   std::string_view topic_name,
                                                   dto::Region workzone)
    : Node(node_name.data()),
      deadtime_(rclcpp::Time(0, 0, RCL_ROS_TIME)),
      workzone_(workzone),
      max_x_speed_(1) {
  publisher_ =
      create_publisher<geometry_msgs::msg::Twist>(topic_name.data(), 10);
  timer_ptr_ = create_wall_timer(
      100ms, std::bind(&WalkingPlatformModelNode::TimerCallback, this));
}

void WalkingPlatformModelNode::TimerCallback() {
  auto locker = std::scoped_lock(mutex_);
  if (deadtime_.seconds() == 0.0 || now() <= deadtime_) {
    publisher_->publish(msg_);
    return;
  }
  publisher_->publish((geometry_msgs::msg::Twist()));
}

void WalkingPlatformModelNode::ShiftY(float shift) {
  RCLCPP_INFO(get_logger(), "Set platform shift: %.2f", shift);
  // SetSpeedY(max_x_speed_);
  // deadtime_ = now() + rclcpp::Duration((shift / max_x_speed_) * powf(10, 9));
}

void WalkingPlatformModelNode::ShiftX(float shift) {
  RCLCPP_WARN(get_logger(), "Don`t use WalkingPlatformModelNode::ShiftX!");
  ShiftY(shift);
}

// HACK: Метод Rotate должен принимать угол, а не скорость
void WalkingPlatformModelNode::Rotate(float speed) {
  // auto locker = std::scoped_lock(mutex_);
  // msg_.angular.set__z(speed);
}

void WalkingPlatformModelNode::SetSpeedY(float speed) {
  // auto locker = std::scoped_lock(mutex_);
  // msg_.linear.set__x(speed);
  // deadtime_ = rclcpp::Time(0, 0, RCL_ROS_TIME);
  RCLCPP_INFO(get_logger(), "Set platform speed: %.2f", speed);
}

void WalkingPlatformModelNode::SetSpeedX(float speed) {
  RCLCPP_WARN(get_logger(), "Don`t use WalkingPlatformModelNode::SetSpeedX!");
  SetSpeedY(speed);
}

dto::Region WalkingPlatformModelNode::get_workzone() const {
  return workzone_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg