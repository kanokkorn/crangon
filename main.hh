#define VERSION 1
#define REVISION 1
#define _DEFAULT_SOURCE

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <thread>
#include <cstdlib>
#include <csignal>


/* unix pipe for gui front-end + syscall for better stdout throughput */
#if defined(__linux__) || defined (__gnu_linux__)
#include <sys/types.h>
#include <sys/ipc.h>
/* currently OpenCV 4.7 dev, might switch to 3.x for BSD license */
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#endif

/* develop on linux, target on *BSD systems */
#if defined(__unix__) || defined(__UNIX__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ipc.h>
#include <limits.h>
#include <linux/limits.h>
#include <linux/param.h>
/* currently OpenCV 4.7 dev, might switch to 3.x for BSD license */
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#endif 

/* enable OpenMP */ 
#ifdef OMP
#include <omp.h>
#endif

/* pre-define camera setting based on webcam */
#define BUF_SIZE 4096
#define COLR_CHAN 3
#define CAM_WIDTH 1280
#define CAM_HEIGHT 720
#define CAMERA_ID 0
#define CAMERA_PATH "/dev/video"

/* fixed resolution cam, no need for dynamic allocation */
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
int img_get_frame(void);
