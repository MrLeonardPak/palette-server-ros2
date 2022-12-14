#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH

#include <geometry_msgs/msg/pose.hpp>
#include <rclcpp/rclcpp.hpp>

#include "dto/pose.hh"
#include "entity/interface/i-equipment-model.hh"
#include "entity/interface/i-manipulator-model.hh"
#include "entity/interface/i-platform-model.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

geometry_msgs::msg::Pose RosPoseCast(dto::Pose const& dto_pose) noexcept;

class IPlatformNode : public rclcpp::Node,
                      public palette_server_api::entity::IPlatformModel {
 public:
  IPlatformNode(std::string name) : Node(std::move(name)){};
  ~IPlatformNode() = default;
};

class IManipulatorNode : public rclcpp::Node,
                         public palette_server_api::entity::IManipulatorModel {
 public:
  IManipulatorNode(std::string name) : Node(std::move(name)){};
  IManipulatorNode(std::string name, rclcpp::NodeOptions const& options)
      : Node(std::move(name), options){};
  ~IManipulatorNode() = default;
};

class IEquipmentNode : public rclcpp::Node,
                       public palette_server_api::entity::IEquipmentModel {
 public:
  IEquipmentNode(std::string name) : Node(std::move(name)){};
  ~IEquipmentNode() = default;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH