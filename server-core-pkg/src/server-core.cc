#include "server-core-pkg/server-core.hh"

#include <chrono>
#include <iostream>
#include <memory>

#include "boost/property-tree.txx"
#include "use_case/auto-control-uc.txx"

#include "adapter-pkg/dobot-manipulator-model-node.hh"
#include "adapter-pkg/painter-model-node.txx"
#include "adapter-pkg/walking-platform-model-node.hh"

using namespace std::chrono_literals;

namespace palette_server_api::lib::ros_foxy::server_core_pkg {
void ServerCore::Run() {
  //   auto auto_control_uc =
  //       std::make_unique<use_case::AutoControlUC<boost::PropertyTree>>();

  // XXX DO HERE!

  //   auto zone = dto::Region({0.0, 0.0}, {0.0, 0.0});
  // std::cout << "Enter start point X Y:\n";
  // std::cin >> zone.points.first.x >> zone.points.first.y;
  // std::cout << "Enter end point X Y:\n";
  // std::cin >> zone.points.second.x >> zone.points.second.y;

  auto platform = std::make_shared<adapter_pkg::WalkingPlatformModelNode>(
      "walking_platform", "cmd_linear", dto::Region({0.0, 0.0}, {0.0, 0.0}));
  //   auto manipulator =
  //   std::make_unique<adapter_pkg::DobotManipulatorModelNode>(
  //       "dobot", dto::Region({0.0, 0.0}, {0.0, 0.0}));
  //   auto equipment =
  //       std::make_unique<adapter_pkg::PainterModelNode<boost::PropertyTree>>(
  //           "painter", dto::Region({0.0, 0.0}, {0.0, 0.0}));

  //   auto params = boost::PropertyTree();
  //   auto robot = std::make_unique<dto::Robot<boost::PropertyTree>>(
  //       1, std::move(platform), std::move(manipulator),
  //       std::move(equipment));

  // while (rclcpp::ok()) {
  //   platform->SetSpeedX(1.0);
  //   std::cout << "Here\n";
  //   rclcpp::sleep_for(3s);
  // }

  platform->SetSpeedX(1.0);
  // rclcpp::spin(platform);
  // platform->SetSpeedX(0.0);
  // rclcpp::sleep_for(2s);
  //   platform->Rotate(1.0);
  //   auto_control_uc->Execute(std::move(robot), zone, params);
}

}  // namespace palette_server_api::lib::ros_foxy::server_core_pkg
