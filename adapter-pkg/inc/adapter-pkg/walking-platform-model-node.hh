#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_HH

#include "i-platform-model.hh"

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class WalkingPlatformModelNode : public rclcpp::Node,
                                 public entity::IPlatformModel {
 public:
  WalkingPlatformModelNode(std::string_view node_name,
                           std::string_view topic_name,
                           dto::Region workzone);
  ~WalkingPlatformModelNode() = default;

  void ShiftX(float) override;
  void ShiftY(float) override;
  void Rotate(float) override;
  void SetSpeedX(float) override;
  void SetSpeedY(float) override;
  dto::Region get_workzone() const override;

 private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  dto::Region workzone_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_WALKING_PLATFORM_MODEL_NODE_H