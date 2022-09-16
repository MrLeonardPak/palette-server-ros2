#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH

#include "i-manipulator-model.hh"

#include "rclcpp/rclcpp.hpp"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class DobotManipulatorModelNode : public rclcpp::Node,
                                  public entity::IManipulatorModel {
 public:
  DobotManipulatorModelNode(std::string_view node_name,
                            std::string_view topic_name,
                            dto::Region workzone);
  ~DobotManipulatorModelNode() = default;

  void SetPoseValue(dto::Pose pose) override;
  void SetPoseSpeed(float speed) override;
  void SetJointValue(int joint_num, float value) override;
  void SetJointSpeed(int joint_num, float speed) override;
  dto::Region get_workzone() const override;

 private:
  dto::Region workzone_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_DOBOT_MANIPULATOR_MODEL_NODE_HH