#include "adapter-pkg/painter-model-node.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

PainterModelNode::PainterModelNode(std::string const& node_name,
                                   dto::props::Equipment props)
    : node_(rclcpp::Node::make_shared(node_name)), props_(props) {}

void PainterModelNode::Enable() {
  // TODO: Code here
  RCLCPP_INFO(node_->get_logger(), "Enable call");
}

void PainterModelNode::Disable() {
  // TODO: Code here
  RCLCPP_INFO(node_->get_logger(), "Disable call");
}

dto::props::Equipment PainterModelNode::get_props() const {
  return props_;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg
