#include "main.hh"

int main(void) {
  signal(SIGINT, sig_handler);
  spdlog::info("   ___                             ");
  spdlog::info("  / __|_ _ __ _ _ _  __ _ ___ _ _  ");
  spdlog::info(" | (__| '_/ _` | ' \\/ _` / _ \\ ' \\ ");
  spdlog::info("  \\___|_| \\__,_|_||_\\__, \\___/_||_|");
  spdlog::info("                    |___/          ");
  spdlog::info("crangon starting");

  /* read settings from config.json */
  std::ifstream ifs("config.json");
  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);
  spdlog::info("Machine ID : 0x{0:x}", obj["machine_id"].asUInt());
  if (ifs.fail()) {
    spdlog::critical("error -> exit, config.json not found!");
    exit(1);
  }
  /* spawn thread */
  std::thread direct (director);
  std::thread perform (performer);
  direct.join();
  perform.join();
  spdlog::info("crangon exitting");
  spdlog::info("shutting down system");
  return 0;
}

static void sig_handler(int signum) {
  spdlog::critical("error -> exit, interrupt signal received.\n");
  exit(signum);
}

static void sys_shutdown(void) {
  system("shutdown -P now");
}
