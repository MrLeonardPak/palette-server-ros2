#include "server-core-pkg/server-core.hh"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "dto/prop-tree.hh"

#include "use_case/auto-control-uc.txx"

#include "adapter-pkg/dobot-manipulator-model-node.hh"
#include "adapter-pkg/painter-model-node.txx"
#include "adapter-pkg/walking-platform-model-node.hh"

using namespace std::chrono_literals;

namespace palette_server_api::lib::ros_foxy::server_core_pkg {
void ServerCore::Run() {
  auto auto_control_uc = std::make_unique<use_case::AutoControlUC>();

  // XXX DO HERE!

  auto zone = dto::Region({0.0, 0.0}, {1.0, 3.0});
  // std::cout << "Enter start point X Y:\n";
  // std::cin >> zone.points.first.x >> zone.points.first.y;
  // std::cout << "Enter end point X Y:\n";
  // std::cin >> zone.points.second.x >> zone.points.second.y;

  auto platform = std::make_shared<adapter_pkg::WalkingPlatformModelNode>(
      "walking_platform", "cmd_linear", dto::Region({0.0, 0.0}, {1.0, 1.0}));
  auto manipulator = std::make_shared<adapter_pkg::DobotManipulatorModelNode>(
      "dobot", dto::Region({0.0, 0.0}, {1.0, 1.0}));
  auto equipment = std::make_shared<adapter_pkg::PainterModelNode>(
      "painter", dto::Region({0.0, 0.0}, {0.1, 1.0}));

  auto props = dto::PropTree();
  props["overlay"] = 0.2f;
  props["z-space"] = 0.1f;
  props["manip-max-speed"] = 1.0f;
  props["manip-y-shift"] = 0.0f;
  props["manip-x-shift"] = 0.0f;
  auto robot =
      std::make_unique<dto::Robot>(1, platform, manipulator, equipment);

  auto executor = rclcpp::executors::StaticSingleThreadedExecutor();
  auto t = std::thread([&executor]() { executor.spin(); });

  executor.add_node(platform);
  executor.add_node(manipulator);
  executor.add_node(equipment);

  auto_control_uc->Execute(std::move(robot), zone, props);
  while (rclcpp::ok()) {
    /* code */
  }
  // rclcpp::spin(platform);
  // platform->SetSpeedX(0.0);
  // rclcpp::sleep_for(2s);
  //   platform->Rotate(1.0);
  //   auto_control_uc->Execute(std::move(robot), zone, params);
}

}  // namespace palette_server_api::lib::ros_foxy::server_core_pkg
