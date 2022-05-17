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
#include <condition_variable>

/* image process */
#include "prog.hh"

/* messaging with GUI  */
#ifdef USE_ZMQ
#include "mq.hh"
#endif

/* collecting data */
#ifdef USE_SQL
#include "sq.hh"
#endif

/* logging */
#include <spdlog/spdlog.h>

/* config and data exchange */
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
/* static void sys_shutdown(void); */
