#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH

#include "i-equipment-model.hh"

#include "rclcpp/rclcpp.hpp"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

template <dto::property_tree_class PropertyTree>
class PainterModelNode : public rclcpp::Node,
                         public entity::IEquipmentModel<PropertyTree> {
 public:
  PainterModelNode(std::string_view node_name,
                   std::string_view topic_name,
                   dto::Region workzone)
      : Node(node_name.data()), workzone_(workzone) {}
  ~PainterModelNode() = default;

  void Enable() override {
    // TODO: Code here
    RCLCPP_INFO(this->get_logger(), "Enable call");
  }
  void SetParams(PropertyTree&& params) override { params_ = params; }
  float CalcRecommendSpeed() const override { return 1.0; }
  dto::Region get_workzone() const override { return workzone_; }

 private:
  dto::Region workzone_;
  PropertyTree params_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH