#include "main.hh"

enum direct_signal { loop, quit, rest };

void director(void) {
  spdlog::info("spawning director");
  spdlog::info("director trying parse config.json");
  std::ifstream ifs("config.json");
  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);
  spdlog::info("Machine ID : 0x{0:x}", obj["machine_id"].asUInt());
  if (ifs.fail()) {
    spdlog::critical("director cannot open file");
    std::terminate();
  }
  /* store variable in local and send to performer */
}
