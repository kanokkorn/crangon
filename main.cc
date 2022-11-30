/*
 * File: main.cc
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 * consider rewrite to be usable next merge
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
  signal(SIGINT, int_handler);
  signal(SIGTSTP, tstp_handler);
  std::cout << "running OpenCV version: " << CV_VERSION << std::endl;
  std::ifstream ifs("config_file.txt");
  if (ifs.fail()) {
    std::cout << "error! 'config_file.txt' not found" << std::endl;
    exit(1);
  }
  std::cout << "machine serial: " << std::endl;
  exit(1);
}
