#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH

#include "rclcpp/rclcpp.hpp"

#include "entity/interface/i-equipment-model.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class PainterModelNode : public entity::IEquipmentModel {
 public:
  PainterModelNode(std::string const& node_name, dto::props::Equipment props);
  ~PainterModelNode() = default;

  void Enable() override;
  void Disable() override;
  dto::props::Equipment get_props() const override;

 private:
  rclcpp::Node::SharedPtr node_;
  dto::props::Equipment props_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH
