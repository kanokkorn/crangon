/*
 * File: main.cc
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#include "main.hh"

std::atomic<bool> exit_thread_flag{false};

int main(void) {
  vid_conf *vidf = new vid_conf;
  signal(SIGINT, sig_handler);
  signal(SIGTSTP, sig_handler);
  spdlog::info("   ___                             ");
  spdlog::info("  / __|_ _ __ _ _ _  __ _ ___ _ _  ");
  spdlog::info(" | (__| '_/ _` | ' \\/ _` / _ \\ ' \\ ");
  spdlog::info("  \\___|_| \\__,_|_||_\\__, \\___/_||_|");
  spdlog::info("                    |___/          ");
  spdlog::info("parsing config.json");

  /* read settings from config.json */
  std::ifstream ifs("config.json");
  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);
  /* TODO: Generate machine IO with UUID or GUID */
  if (ifs.fail()) {
    spdlog::critical("error -> exit, config.json not found!");
    exit(1);
  }
  vidf->vid_id = obj["camera_id"].asUInt();
  spdlog::info("Machine ID : 0x{0:x}", obj["machine_id"].asUInt());
  spdlog::info("Video path for debug : {0}", obj["video"].asString());
  spdlog::info("Camera  ID : {0:d}", vidf->vid_id);

#ifdef USE_VID
  auto future = std::async(get_frame, obj["video"].asString(), vidf->vid_width, vidf->vid_height);
#else
  auto future = std::async(get_frame, vidf->vid_id, vidf->vid_width, vidf->vid_height);
#endif
  if (future.get()) {
    std::cout << "exit\n";
    exit(1);
  }
  spdlog::info("crangon exitting");
  spdlog::info("shutting down system");
  return 0;
}

static void sig_handler(int signum) {
  if (signum == 2) {
    spdlog::critical("interrupt received. exit\n");
    stop = 1;
    exit(signum);
  } else if (signum == 20) {
    spdlog::critical("terminal stop. pausing for 30 sec\n");
    sleep(30);
    spdlog::critical("timer expired. countinuing\n");
  }
}
