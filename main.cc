/*
 * File: main.cc
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#include "main.hh"

/* CTRL + C handler */

void sig_handler(int signum) {
  if (signum == 2) {
    spdlog::critical("interrupt received. exit\n");
    exit(signum);
  } else if (signum == 20) {
    spdlog::critical("terminal stop. pausing for 30 sec\n");
    sleep(30);
    spdlog::critical("timer expired. countinuing\n");
  }
}

int main(void) {
  vid_conf *vidf = new vid_conf;
  signal(SIGINT, sig_handler);
  signal(SIGTSTP, sig_handler);
  spdlog::info("running OpenCV version: {}", CV_VERSION);
  spdlog::info("parsing config.json");
  std::ifstream ifs("config.json");
  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);
  if (ifs.fail()) {
    spdlog::critical("error -> exit, config.json not found!");
    exit(1);
  }
  spdlog::info("SERIAL: {}", obj["device_serial"].asString());
  if (obj["enable_cam"].asBool()) {
    vidf->vid_id = obj["camera_id"].asUInt();
    spdlog::info("Camera Model: {0:d}", vidf->vid_id);
    try {
      auto camera = std::async(
          get_frame,
          vidf->vid_id,
          vidf->vid_width,
          vidf->vid_height
          );
    }
    catch (cv::Exception& e) {
      spdlog::warn("cannot open camera: {}", obj["video"].asString());
    }
  } else {
    spdlog::warn(
        "enable_cam is set to false, crangon will use video path instead: {}",
        obj["video"].asString()
        );
    vidf->vid_path = obj["camera_id"].asString();
  }
  exit(1);
}
