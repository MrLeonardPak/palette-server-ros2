#include "adapter-pkg/painter-model-node.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

PainterModelNode::PainterModelNode(std::string node_name, dto::Region workzone)
    : IEquipmentNode(std::move(node_name)), workzone_(workzone) {}

void PainterModelNode::Enable() {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Enable call");
}

void PainterModelNode::Disable() {
  // TODO: Code here
  RCLCPP_INFO(this->get_logger(), "Disable call");
}

void PainterModelNode::SetParams(dto::PropTree&& params) {
  params_ = params;
}

float PainterModelNode::CalcRecommendSpeed() const {
  return 0.6;
}

dto::Region PainterModelNode::get_workzone() const {
  return workzone_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg