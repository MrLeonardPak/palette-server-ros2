#ifndef PALETTE_SERVER_API_LIB_ROS_FOXY_SERVER_CORE_PKG_SERVER_CORE_HH
#define PALETTE_SERVER_API_LIB_ROS_FOXY_SERVER_CORE_PKG_SERVER_CORE_HH

namespace palette_server_api::lib::ros_foxy::server_core_pkg {

class ServerCore {
 public:
  ServerCore() = default;
  ~ServerCore() = default;

  void Run();
};

}  // namespace palette_server_api::lib::ros_foxy::server_core_pkg

#endif  // PALETTE_SERVER_API_LIB_ROS_FOXY_SERVER_CORE_PKG_SERVER_CORE_HH