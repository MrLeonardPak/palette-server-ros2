#include "adapter-pkg/dobot-manipulator-model-node.hh"

#include <chrono>

#include <moveit/trajectory_processing/iterative_time_parameterization.h>

// #include "adapter-pkg/adapter.hh"

using namespace std::chrono_literals;

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

DobotManipulatorModelNode::DobotManipulatorModelNode(std::string node_name,
                                                     dto::Region workzone)
    : IManipulatorNode(
          std::move(node_name),
          rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(
              true)),
      workzone_(workzone),
      move_group_node_(rclcpp::Node::make_shared(
          "move_group_interface_tutorial",
          rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(
              true))),
      move_group_(move_group_node_, "dobot_arm"),
      move_speed_(0.0) {}

void DobotManipulatorModelNode::MoveTo(dto::Pose pose) {
  // TODO: Code here
  auto target_pose = RosPoseCast(std::move(pose));
  waypoints_.push_back(target_pose);

  moveit_msgs::msg::RobotTrajectory trajectory;
  double const jump_threshold = 0.0;
  double const eef_step = 0.01;
  auto fraction = move_group_.computeCartesianPath(waypoints_, eef_step,
                                                   jump_threshold, trajectory);

  if (fraction > 0.8) {
    // // The trajectory needs to be modified so it will include velocities as
    // // well. First to create a RobotTrajectory object
    robot_trajectory::RobotTrajectory rt(
        move_group_.getCurrentState()->getRobotModel(), move_group_.getName());

    // Second get a RobotTrajectory from trajectory
    rt.setRobotTrajectoryMsg(*move_group_.getCurrentState(), trajectory);

    // Thrid create a IterativeParabolicTimeParameterization object
    trajectory_processing::IterativeParabolicTimeParameterization iptp;
    // Fourth compute computeTimeStamps
    bool success = iptp.computeTimeStamps(rt, move_speed_);
    if (success) {
      RCLCPP_INFO(get_logger(), "Computed time stamp SUCCESS");
    } else {
      // Исключение, если нет что то не так с параметризацией
      throw std::runtime_error("Time Parameterization Fail!");
    }
    // Get RobotTrajectory_msg from RobotTrajectory
    rt.getRobotTrajectoryMsg(trajectory);

    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    my_plan.trajectory_ = trajectory;

    RCLCPP_INFO(get_logger(), "Cartesian path SUCCESS (%.2f%% acheived)",
                fraction * 100.0);
    move_group_.execute(my_plan);
  } else {
    move_group_.setPoseTarget(target_pose);
    move_group_.setMaxVelocityScalingFactor(move_speed_);
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;

    bool success = (move_group_.plan(my_plan) ==
                    moveit::planning_interface::MoveItErrorCode::SUCCESS);

    if (success) {
      RCLCPP_INFO(get_logger(), "Pose goal SUCCESS");
    } else {
      // Исключение, если нет пути
      std::stringstream ss;
      ss << "No PATH! point: x - " << target_pose.position.x << "; y - "
         << target_pose.position.y << "; z - " << target_pose.position.z
         << "; orientation: x - " << target_pose.orientation.x << "; y - "
         << target_pose.orientation.y << "; z - " << target_pose.orientation.z
         << "; w - " << target_pose.orientation.w << std::endl;
      throw std::runtime_error(ss.str());
    }

    move_group_.move();
  }
  waypoints_.clear();
  move_group_.clearPoseTargets();

  RCLCPP_INFO(
      get_logger(), "Set Pose Value: point: x-'%.2f' y-'%.2f' z-'%.2f' ",
      // "orient: x-'%.2f' y-'%.2f' z-'%.2f' w-'%.2f'",
      target_pose.position.x, target_pose.position.y, target_pose.position.z,
      target_pose.orientation.x, target_pose.orientation.y,
      target_pose.orientation.z, target_pose.orientation.w);
}

void DobotManipulatorModelNode::set_move_speed(float speed) {
  // TODO: Code here
  move_speed_ = speed;
  RCLCPP_INFO(get_logger(), "Set Pose Speed: %.2f", speed);
}

dto::Region DobotManipulatorModelNode::get_workzone() const {
  return workzone_;
}

// Moveit go to home position
void DobotManipulatorModelNode::GoHome() {
  move_group_.setNamedTarget("home");
  move_group_.setMaxVelocityScalingFactor(move_speed_);
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  bool success = (move_group_.plan(my_plan) ==
                  moveit::planning_interface::MoveItErrorCode::SUCCESS);

  if (success) {
    RCLCPP_INFO(get_logger(), "Pose goal SUCCESS");
  } else {
    // Исключение, если нет пути
    std::stringstream ss;
    ss << "No PATH to home!" << std::endl;
    throw std::runtime_error(ss.str());
  }

  move_group_.move();
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg