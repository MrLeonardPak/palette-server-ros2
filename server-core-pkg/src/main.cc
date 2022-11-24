#include "ui-pkg/consol-ui.hh"

#include <memory>

#include "rclcpp/rclcpp.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  std::make_unique<palette_server_ui::ConsolUI>()->Run();

  rclcpp::shutdown();
  return 0;
}