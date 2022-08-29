#define _POSIX_SOURCE

#include <iostream>
#include <cstdlib>
#include <csignal>
#include <string>
#include <fstream>
#include <thread>
#include <atomic>
#include <chrono>
#include <future>
#include <condition_variable>

#include <spdlog/spdlog.h>
#include <jsoncpp/json/json.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <spdlog/spdlog.h>

typedef struct {
  uint8_t vid_id;
  uint16_t vid_width;
  uint16_t vid_height;
  std::string vid_path;
}vid_conf;

typedef struct {
  long long img_dat;
}data;

volatile sig_atomic_t stop;
