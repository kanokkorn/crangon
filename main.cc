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
  /* reserved memory for camera configuration */
  vid_conf *vidf = new vid_conf;

  /* setup signal handler */
  signal(SIGINT, int_handler);
  signal(SIGTSTP, tstp_handler);

  /*
   * looking for better way to log & parse config file
   * spdlog::info("running OpenCV version: {}", CV_VERSION);
   * spdlog::info("parsing config.json");
   */
  /* check config file and OpenCV version */
  std::cout << "running OpenCV version: " << CV_VERSION << std::endl;
  std::ifstream ifs("config_file.txt");
  if (ifs.fail()) {
    std::cout << "error! 'config_file.txt' not found" << std::endl;
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
      std::cout << "can't open camera, abort" << std::endl;
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
