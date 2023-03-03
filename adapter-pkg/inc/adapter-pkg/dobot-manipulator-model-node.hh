#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH

#include <moveit/move_group_interface/move_group_interface.h>
#include <rclcpp/rclcpp.hpp>

#include "adapter-pkg/adapter.hh"
#include "entity/interface/i-manipulator-model.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class DobotManipulatorModelNode : public MiniNode,
                                  public entity::IManipulatorModel {
 public:
  DobotManipulatorModelNode(rclcpp::Executor::SharedPtr executor,
                            std::string const& node_name,
                            dto::props::Manipulator props);
  ~DobotManipulatorModelNode() = default;

  void GoTo(dto::Pose pose) override;
  void GoTo(std::string const& pose_name) override;
  void set_eef_speed(float speed) override;
  dto::props::Manipulator get_props() const override;

 private:
  dto::props::Manipulator props_;
  moveit::planning_interface::MoveGroupInterface move_group_;
  std::vector<geometry_msgs::msg::Pose> waypoints_;
  float move_speed_ = 0.0f;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH
