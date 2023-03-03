#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH

#include <geometry_msgs/msg/pose.hpp>
#include <rclcpp/rclcpp.hpp>

#include "dto/pose.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

geometry_msgs::msg::Pose RosPoseCast(dto::Pose const& dto_pose) noexcept;

class MiniNode {
 public:
  MiniNode(rclcpp::Executor::SharedPtr executor, std::string node_name)
      : executor_(executor), node_(rclcpp::Node::make_shared(node_name)) {
    StartNodeExec();
  };
  ~MiniNode() { StopNodeExec(); };

  void StartNodeExec() { executor_->add_node(node_); };
  void StopNodeExec() { executor_->remove_node(node_); };

 protected:
  rclcpp::Executor::SharedPtr executor_;
  rclcpp::Node::SharedPtr node_;
};

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH
