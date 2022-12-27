#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH

#include <moveit/move_group_interface/move_group_interface.h>
#include <rclcpp/rclcpp.hpp>

#include "adapter-pkg/adapter.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class DobotManipulatorModelNode : public IManipulatorNode {
 public:
  DobotManipulatorModelNode(std::string node_name, dto::Region workzone);
  ~DobotManipulatorModelNode() = default;

  void MoveTo(dto::Pose pose) override;
  void set_move_speed(float speed) override;
  dto::Region get_workzone() const override;
  void GoHome() override;

 private:
  dto::Region workzone_;
  rclcpp::Node::SharedPtr move_group_node_;
  moveit::planning_interface::MoveGroupInterface move_group_;
  std::vector<geometry_msgs::msg::Pose> waypoints_;
  float move_speed_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH