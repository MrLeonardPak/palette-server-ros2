#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_HH

#include <mutex>

#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>

#include "adapter-pkg/adapter.hh"
#include "platform_msg/msg/cmd_linear.hpp"
#include "platform_msg/msg/cmd_rot.hpp"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class WalkingPlatformModelNode : public IPlatformNode {
 public:
  WalkingPlatformModelNode(std::string node_name,
                           std::string linear_topic_name,
                           std::string rotate_topic_name,
                           dto::Region workzone);
  ~WalkingPlatformModelNode() = default;

  void ShiftX(float) override;
  void ShiftY(float) override;
  void Rotate(float) override;
  void set_x_speed(float) override;
  void set_y_speed(float) override;
  void set_angular_speed(float) override;
  dto::Region get_workzone() const override;

 private:
  rclcpp::Publisher<platform_msg::msg::CmdLinear>::SharedPtr linear_publisher_;
  rclcpp::Publisher<platform_msg::msg::CmdRot>::SharedPtr rotate_publisher_;

  // geometry_msgs::msg::Twist msg_;
  dto::Region workzone_;
  float linear_speed_;
  float angular_speed_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_H