#include "adapter-pkg/dobot-manipulator-model-node.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

DobotManipulatorModelNode::DobotManipulatorModelNode(
    std::string_view node_name,
    std::string_view topic_name,
    dto::Region workzone)
    : Node(node_name.data()), workzone_(workzone) {}

void DobotManipulatorModelNode::SetPoseValue(dto::Pose pose) {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(),
              "Set Pose Value: point: x-'%d' y-'%d' z-'%d' orient: x-'%d' "
              "y-'%d' z-'%d' w-'%d'",
              pose.position.x, pose.position.y, pose.position.z,
              pose.orientetion.x, pose.orientetion.y, pose.orientetion.z,
              pose.orientetion.w);
}
void DobotManipulatorModelNode::SetPoseSpeed(float speed) {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Set Pose Speed: '%d'", speed);
}
void DobotManipulatorModelNode::SetJointValue(int joint_num, float value) {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Set Joint '%d' Value: '%d'", joint_num,
              value);
}
void DobotManipulatorModelNode::SetJointSpeed(int joint_num, float speed) {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Set Joint '%d' Speed: '%d'", joint_num,
              speed);
}
dto::Region DobotManipulatorModelNode::get_workzone() const {
  return workzone_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg