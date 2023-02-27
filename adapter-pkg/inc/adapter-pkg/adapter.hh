#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH

#include <geometry_msgs/msg/pose.hpp>

#include "dto/pose.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

geometry_msgs::msg::Pose RosPoseCast(dto::Pose const& dto_pose) noexcept;

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_ADAPTER_PKG_HH
