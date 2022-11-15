#include "server-core-pkg/server-core.hh"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dto/prop-tree.hh"

#include "use-case/auto-control-uc.hh"

#include "adapter-pkg/dobot-manipulator-model-node.hh"
#include "adapter-pkg/painter-model-node.txx"
#include "adapter-pkg/walking-platform-model-node.hh"

using namespace std::chrono_literals;

namespace palette_server_api::lib::ros_foxy::server_core_pkg {
void ServerCore::Run() {
  // XXX DO HERE!

  auto zone = dto::Region({0.0, 0.0}, {1.0, 3.0});

  auto platform = std::make_shared<adapter_pkg::WalkingPlatformModelNode>(
      "walking_platform", "cmd_linear", dto::Region({0.0, 0.0}, {1.0, 1.0}));
  auto manipulator = std::make_shared<adapter_pkg::DobotManipulatorModelNode>(
      "dobot", dto::Region({0.0, 0.0}, {1.0, 1.0}));
  auto equipment = std::make_shared<adapter_pkg::PainterModelNode>(
      "painter", dto::Region({0.0, 0.0}, {0.1, 1.0}));

  auto props = dto::PropertyAutoControlUC();
  props.z_space = 0.1f;
  props.manip_max_speed = 1.0f;
  props.overlay = 0.2f;
  props.manip_in_platform.x = 0.2;
  props.manip_in_platform.y = 0.2;
  props.manip_in_platform.z = 0.1;
  auto robot =
      std::make_unique<dto::Robot>(1, platform, manipulator, equipment);

  auto executor = rclcpp::executors::StaticSingleThreadedExecutor();
  auto t = std::thread([&executor]() { executor.spin(); });

  executor.add_node(platform);
  executor.add_node(manipulator);
  executor.add_node(equipment);

  std::make_shared<use_case::AutoControlUC>()->Execute(std::move(robot), zone,
                                                       props);

  while (rclcpp::ok()) {
  }
}

}  // namespace palette_server_api::lib::ros_foxy::server_core_pkg
