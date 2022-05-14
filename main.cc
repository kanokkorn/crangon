/*
 * File: main.cc
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#include "main.hh"

int main(void) {
  signal(SIGINT, sig_handler);
  signal(SIGTSTP, sig_handler);
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
  /*
   * TODO: Generate machine IO with UUID or GUID
   */
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
  if (signum == 2) {
    spdlog::critical("interrupt received. exit\n");
    exit(signum);
  } else if (signum == 20) {
    spdlog::critical("terminal stop. pausing for 30 sec\n");
    sleep(30);
    spdlog::critical("timer expired. countinuing\n");
  }
}

static void sys_shutdown(void) {
  system("shutdown -P now");
}
