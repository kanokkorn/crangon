#define _POSIX_SOURCE

#ifndef __has_builtin
  #define __has_builtin(x) 0
#endif

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
  uint8_t vid_width;
  uint8_t vid_height;
}vid_conf;

typedef struct {
  uint16_t id;
}machine_id;

volatile sig_atomic_t stop;

