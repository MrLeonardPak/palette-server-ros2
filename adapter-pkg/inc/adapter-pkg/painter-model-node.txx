#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH

#include "dto/prop-tree.hh"

#include "entity/interface/i-equipment-model.hh"

#include "rclcpp/rclcpp.hpp"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class PainterModelNode : public rclcpp::Node, public entity::IEquipmentModel {
 public:
  PainterModelNode(std::string_view node_name, dto::Region workzone)
      : Node(node_name.data()), workzone_(workzone) {}
  ~PainterModelNode() = default;

  void Enable() override {
    // TODO: Code here
    RCLCPP_INFO(this->get_logger(), "Enable call");
  }
  void SetParams(dto::PropTree&& params) override { params_ = params; }
  float CalcRecommendSpeed() const override { return 0.6; }
  dto::Region get_workzone() const override { return workzone_; }

 private:
  dto::Region workzone_;
  dto::PropTree params_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH