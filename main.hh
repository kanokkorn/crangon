#define VERSION 1.1
#define REVISION A
#define _POSIX_SOURCE

/* common */
#include <iostream>
#include <cstdlib>
#include <csignal>
#include <string>
#include <fstream>
#include <thread>

/* IPC */
#include <sys/types.h>
#include <sys/ipc.h>

/* syscall */
#include <unistd.h>
#include <sys/types.h>

/* Opencv */
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/* video input config */
typedef struct {
  uint8_t vid_id;
  uint16_t vid_width;
  uint16_t vid_height;
  std::string vid_path;
}vid_conf;

/* output data struct */
typedef struct {
  uint32_t real_out;
  uint32_t average;
  int32_t computer_buf;
  int32_t computer_now;
}output_data;

cv::Mat img_counter(cv::Mat input);
int img_get_frame(uint8_t cam_id, uint8_t vid_width, uint8_t vid_height);
