#include "adapter-pkg/adapter.hh"

#include "adapter-pkg/dobot-manipulator-model-node.hh"
#include "adapter-pkg/painter-model-node.hh"
#include "adapter-pkg/walking-platform-model-node.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

geometry_msgs::msg::Pose RosPoseCast(dto::Pose const& dto_pose) noexcept {
  auto ros_pose = geometry_msgs::msg::Pose();
  ros_pose.position.set__x(dto_pose.position.x)
      .set__y(dto_pose.position.y)
      .set__z(dto_pose.position.z);
  ros_pose.orientation.set__w(dto_pose.orientation.w)
      .set__x(dto_pose.orientation.x)
      .set__y(dto_pose.orientation.y)
      .set__z(dto_pose.orientation.z);
  return ros_pose;
}

std::unique_ptr<dto::Robot> TmpGetRobot::GetRobot(int id) {
  // auto props_robot = dto::props::Robot();
  // props_robot.id = id;
  // props_robot.translation_vector = {0.65, 0.0, 0.1};
  // props_robot.workzone = {{0.0, 0.0}, {0.0, 0.0}};

  // auto props_platform = dto::props::Platform();
  // props_platform.max_speed = 1.0f;
  // props_platform.dimension = dto::Region2D({0.0, 0.0}, {1.0, 1.7});

  auto robot = std::make_unique<dto::Robot>(
      dto::props::Robot(),
      std::make_unique<WalkingPlatformModelNode>("walking_platform",
                                                 "cmd_linear", "cmd_rotate",
                                                 dto::props::Platform{}),
      std::make_unique<DobotManipulatorModelNode>("dobot",
                                                  dto::props::Manipulator{}),
      std::make_unique<PainterModelNode>("painter", dto::props::Equipment{}));
  return robot;
  // return std::make_unique<dto::Robot>(
  //     dto::props::Robot(id, {0.65, 0.0, 0.1}, {{0.0, 0.0}, {0.0, 0.0}}),
  //     std::make_unique<WalkingPlatformModelNode>(
  //         "walking_platform", "cmd_linear", "cmd_rotate",
  //         dto::Region2D({0.0, 0.0}, {1.0, 1.7})),
  //     std::make_unique<DobotManipulatorModelNode>(
  //         "dobot", dto::Region2D({0.0, 0.0}, {1.0, 1.0})),
  //     std::make_unique<PainterModelNode>(
  //         "painter", dto::Region2D({0.0, 0.0}, {0.1, 0.1})));
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg
