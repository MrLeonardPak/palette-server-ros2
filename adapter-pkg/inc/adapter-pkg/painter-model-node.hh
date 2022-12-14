#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH

#include "rclcpp/rclcpp.hpp"

#include "adapter-pkg/adapter.hh"

#include "dto/prop-tree.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

class PainterModelNode : public IEquipmentNode {
 public:
  PainterModelNode(std::string node_name, dto::Region workzone);
  ~PainterModelNode() = default;

  void Enable() override;
  void Disable() override;
  void SetParams(dto::PropTree&& params) override;
  float CalcRecommendSpeed() const override;
  dto::Region get_workzone() const override;

 private:
  dto::Region workzone_;
  dto::PropTree params_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_PAINTER_MODEL_NODE_HH