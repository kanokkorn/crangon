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
  spdlog::info("Camera  ID : {0:d}", vidf->vid_id);

  auto future = std::async(get_frame, vidf->vid_id, vidf->vid_width, vidf->vid_height);
  while (future.get()) {
  //std::thread prog (get_frame, vidf->vid_id, vidf->vid_width, vidf->vid_height);
  #ifdef USE_ZMQ
    std::thread mq (send_mq);
    mq.join();
  #endif
  #ifdef USE_SQL
    std::thread sq (send_sq);
    sq.join();
  #endif
  }
  /* spawn thread */

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

/* in-case on real hardware
}
*/
