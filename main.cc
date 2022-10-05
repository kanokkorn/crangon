/*
 * File: main.cc
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#include "main.hh"

void tstp_handler(int signum) {
  spdlog::warn("SIGTSTP received - pausing");
  /* pause program for x seconds */
}

void kill_handler(int signum) {
  spdlog::critical("SIGKILL received. unexpected error will be report\n");
  /* shutdown everything */
}

void int_handler(int signum) {
  spdlog::warn("SIGINT received.");
}

int main(void) {
  vid_conf *vidf = new vid_conf;

  /* setup signal handler */
  signal(SIGINT, int_handler);
  signal(SIGTSTP, tstp_handler);

  /* looking for better way to log & parse config file*/
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
      img_get_frame(vidf->vid_id, vidf->vid_width, vidf->vid_height);
      //auto camera = std::async(
      //    img_get_frame,
      //    vidf->vid_id,
      //    vidf->vid_width,
      //    vidf->vid_height
      //    );
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
