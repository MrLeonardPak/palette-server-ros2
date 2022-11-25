#include "adapter-pkg/dobot-manipulator-model-node.hh"

#include <chrono>

#include <moveit/trajectory_processing/iterative_time_parameterization.h>

using namespace std::chrono_literals;

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

DobotManipulatorModelNode::DobotManipulatorModelNode(std::string_view node_name,
                                                     dto::Region workzone)
    : Node(
          node_name.data(),
          rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(
              true)),
      workzone_(workzone),
      move_group_node_(rclcpp::Node::make_shared(
          "move_group_interface_tutorial",
          rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(
              true))),
      move_group_(move_group_node_, "dobot_arm") {}

void DobotManipulatorModelNode::SetPoseValue(dto::Pose pose) {
  // TODO: Code here
  auto target_pose = geometry_msgs::msg::Pose();
  target_pose.position.set__x(pose.position.x)
      .set__y(pose.position.y)
      .set__z(pose.position.z);
  target_pose.orientation.set__w(pose.orientetion.w)
      .set__x(pose.orientetion.x)
      .set__y(pose.orientetion.y)
      .set__z(pose.orientetion.z);
  waypoints_.push_back(target_pose);

  moveit_msgs::msg::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  auto fraction = move_group_.computeCartesianPath(waypoints_, eef_step,
                                                   jump_threshold, trajectory);

  if (fraction < 0.7) {
    move_group_.setPoseTarget(target_pose);
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;

    bool success = (move_group_.plan(my_plan) ==
                    moveit::planning_interface::MoveItErrorCode::SUCCESS);

    RCLCPP_INFO(get_logger(), "Visualizing plan 1 (pose goal) %s",
                success ? "" : "FAILED");
    move_group_.move();
  } else {
    RCLCPP_INFO(get_logger(),
                "Visualizing plan 4 (Cartesian path) (%.2f%% acheived)",
                fraction * 100.0);
    move_group_.execute(trajectory);
  }

  RCLCPP_INFO(
      get_logger(), "Set Pose Value: point: x-'%.2f' y-'%.2f' z-'%.2f' ",
      // "orient: x-'%.2f' y-'%.2f' z-'%.2f' w-'%.2f'",
      target_pose.position.x, target_pose.position.y, target_pose.position.z,
      target_pose.orientation.x, target_pose.orientation.y,
      target_pose.orientation.z, target_pose.orientation.w);
  waypoints_.clear();
  move_group_.clearPoseTargets();
  rclcpp::sleep_for(10s);
}
void DobotManipulatorModelNode::SetPoseSpeed(float speed) {
  // TODO: Code here
  static int count = 1;
  RCLCPP_INFO(get_logger(), "%d Set Pose Speed: %.2f", count++, speed);
}
void DobotManipulatorModelNode::SetJointValue(int joint_num, float value) {
  // TODO: Code here
  RCLCPP_INFO(get_logger(), "Set Joint '%d' Value: '%.2f'", joint_num, value);
}
void DobotManipulatorModelNode::SetJointSpeed(int joint_num, float speed) {
  // TODO: Code here
  RCLCPP_INFO(get_logger(), "Set Joint '%d' Speed: '%.2f'", joint_num, speed);
}
dto::Region DobotManipulatorModelNode::get_workzone() const {
  return workzone_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg