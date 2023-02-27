#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PARAMS_DB_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PARAMS_DB_HH

#include "rclcpp/rclcpp.hpp"

#include "gateway/i-get-robot.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

struct RobotRaw {
  std::string platform_node;
  std::string manipulator_node;
  std::string equipment_node;
};

class ParamDB : public gateway::IGetRobot {
 public:
  ParamDB(std::string const& node_name, rclcpp::Executor::SharedPtr executor);
  ~ParamDB() = default;

  std::unique_ptr<dto::Robot> GetRobot(int id) override;

 private:
  rclcpp::Node::SharedPtr node_;
  rclcpp::Executor::SharedPtr executor_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PARAMS_DB_HH
