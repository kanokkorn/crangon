#define __GNU_SOURCE

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
#include <condition_variable>

/* image processing */
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

/* messaging with GUI  */
#include <zmq.hpp>

/* collecting data */
#include <sqlite3.h>

/* offline logging */
#include <spdlog/spdlog.h>

/* for setting file in json */
#include <jsoncpp/json/json.h>

typedef struct {
  uint8_t vid_id;
  uint8_t vid_width;
  uint8_t vid_height;
}vid_conf;

typedef struct {
  uint16_t id;
}machine_id;

/* system handler */
static void sig_handler(int signum);
static void sys_shutdown(void);

/* functions */
void director(void);
void performer(void);
