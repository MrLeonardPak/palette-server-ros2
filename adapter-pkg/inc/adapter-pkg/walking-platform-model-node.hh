#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_HH

#include <mutex>

#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>

#include "adapter-pkg/adapter.hh"
#include "entity/interface/i-platform-model.hh"
#include "platform_msg/msg/cmd_linear.hpp"
#include "platform_msg/msg/cmd_rot.hpp"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class WalkingPlatformModelNode : public MiniNode,
                                 public entity::IPlatformModel {
 public:
  WalkingPlatformModelNode(rclcpp::Executor::SharedPtr executor,
                           std::string const& node_name,
                           std::string const& linear_topic_name,
                           std::string const& rotate_topic_name,
                           dto::props::Platform props);
  ~WalkingPlatformModelNode() = default;

  void ShiftX(float) override;
  void ShiftY(float) override;
  void Rotate(float) override;
  void set_x_vel(float) override;
  void set_y_vel(float) override;
  void set_ang_vel(float) override;
  dto::props::Platform get_props() const override;

 private:
  rclcpp::Publisher<platform_msg::msg::CmdLinear>::SharedPtr linear_publisher_;
  rclcpp::Publisher<platform_msg::msg::CmdRot>::SharedPtr rotate_publisher_;
  dto::props::Platform props_;
  float linear_speed_;
  float angular_speed_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_H
