#include "adapter-pkg/params-db.hh"

#include "adapter-pkg/dobot-manipulator-model-node.hh"
#include "adapter-pkg/painter-model-node.hh"
#include "adapter-pkg/walking-platform-model-node.hh"
#include "dto/region.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

ParamDB::ParamDB(std::string const& node_name,
                 rclcpp::Executor::SharedPtr executor)
    : node_(rclcpp::Node::make_shared(node_name)), executor_(executor) {}

std::unique_ptr<dto::Robot> ParamDB::GetRobot(int id) {
  // TODO Выгружать данные из параметров
  auto robot = std::make_unique<dto::Robot>(
      dto::props::Robot{
          id, {0.65, 0.0, 0.1}, dto::Region2D{{{0.0, 0.0}, {0.0, 0.0}}}},
      std::make_unique<WalkingPlatformModelNode>(
          executor_, "walking_platform", "cmd_linear", "cmd_rotate",
          dto::props::Platform{1.0, dto::Region2D{{{0.0, 0.0}, {1.0, 1.7}}}}),
      std::make_unique<DobotManipulatorModelNode>(executor_, "dobot",
                                                  dto::props::Manipulator{1.0}),
      std::make_unique<PainterModelNode>(
          executor_, "painter",
          dto::props::Equipment{1.0, dto::Region2D{{{0.0, 0.0}, {0.1, 0.1}}}}));
  return robot;
}
}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg
