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
  std::cout << "machine serial: " << std::endl;
  /* check if camera is connected from interface */
  exit(1);
}
