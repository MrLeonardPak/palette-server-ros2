#include <memory>

#include "rclcpp/rclcpp.hpp"

#include "adapter-pkg/params-db.hh"
#include "ui-pkg/consol-ui.hh"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  auto executor = rclcpp::executors::SingleThreadedExecutor::make_shared();
  auto t = std::thread([&]() { executor->spin(); });
  auto db =
      std::make_shared<palette_server_api::lib::ros_foxy::adapter_pkg::ParamDB>(
          "robot_db", executor);
  std::make_unique<palette_server_ui::ConsolUI>(db, [&]() {
    executor->cancel();
    t.join();
  })->Run();

  rclcpp::shutdown();
  return 0;
}
