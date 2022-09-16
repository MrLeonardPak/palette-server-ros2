#include "server-core.hh"

#include <memory>

int main() {
  std::make_unique<
      palette_server_api::lib::ros_foxy::server_core_pkg::ServerCore>()
      ->Run();

  return 0;
}