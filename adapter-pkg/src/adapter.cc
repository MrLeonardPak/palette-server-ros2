#include "adapter-pkg/adapter.hh"

namespace palette_server_api::lib::ros_foxy::adapter_pkg {

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

}  // namespace palette_server_api::lib::ros_foxy::adapter_pkg
