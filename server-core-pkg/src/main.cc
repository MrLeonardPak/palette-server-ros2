#include "server-core-pkg/server-core.hh"

#include <memory>

#include "rclcpp/rclcpp.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  std::make_unique<
      palette_server_api::lib::ros_foxy::server_core_pkg::ServerCore>()
      ->Run();

  rclcpp::shutdown();
  return 0;
}