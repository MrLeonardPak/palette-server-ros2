#include "server-core.hh"

#include <memory>

#include "template/auto-control-uc.txx"
#include "template/property-tree.txx"

#include "adapter-pkg/dobot-manipulator-model-node.hh"
#include "adapter-pkg/template/painter-model-node.txx"
#include "adapter-pkg/walking-platform-model-node.hh"

namespace palette_server_api::lib::ros_foxy::server_core_pkg {

void ServerCore::Run() {
  auto auto_control_uc =
      std::make_unique<use_case::AutoControlUC<boost::PropertyTree>>();

  // XXX DO HERE!

  auto_control_uc->Execute(robot, zone, params);
}

}  // namespace palette_server_api::lib::ros_foxy::server_core_pkg
