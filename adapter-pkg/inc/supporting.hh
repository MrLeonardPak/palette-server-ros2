#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_SUPPORTING_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_SUPPORTING_HH

#include <geometry_msgs/msg/pose.hpp>

#include "dto/pose.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg::supporting {

geometry_msgs::msg::Pose RosPoseCast(dto::Pose const& dto_pose) noexcept {
  auto ros_pose = geometry_msgs::msg::Pose();
  ros_pose.position.set__x(dto_pose.position.x)
      .set__y(dto_pose.position.y)
      .set__z(dto_pose.position.z);
  ros_pose.orientation.set__w(dto_pose.orientation.w)
      .set__x(dto_pose.orientation.x)
      .set__y(dto_pose.orientation.y)
      .set__z(dto_pose.orientation.z);
  return ros_pose;
}

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg::supporting

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_SUPPORTING_HH