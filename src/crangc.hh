/* pre-define value for makefile */
#define VERSION   1
#define REVISION  1

/* std header */
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <fstream>
#include <syslog.h>
#include <functional>

/* time */
#include <chrono>
#include <ctime>
#include <thread> 

/* networking */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>

/* unix pipe for gui front-end */
#if defined(__linux__) || defined (__aarch64__)
#define   PLATFORM "x86_64 Linux"
#include <sys/types.h>
#include <sys/ipc.h>
#endif

/* header for arm64 linux */
#if defined(__linux__) || defined (__aarch64__)
#define   PLATFORM "x86_64 Linux"
#include <sys/types.h>
#include <sys/ipc.h>
#endif

/* 
 *  prototyping  ->  x86 & Aarch64 linux
 *  deploying    ->  Aarch64 FreeBSD img
 */
#if defined(__unix__) || defined(__UNIX__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ipc.h>
#include <linux/limits.h>
#include <linux/param.h>

/* include for pkgconfig */
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/opencv_modules.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>


/* include for direct linking */
#include <opencv4/opencv2/core/core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core/cvstd_wrapper.hpp>
#include <opencv4/opencv2/video/background_segm.hpp>
#include <opencv4/opencv2/videoio.hpp>
#endif 

/* logging */
#include <spdlog/spdlog.h>

/* might need OMP for threading */ 
#ifdef OMP
#include <omp.h>
#endif

#define ESC_CMD "rst"

/* colour terminal */
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RST "\x1B[0m"


#ifndef CAMERA_PATH
#define CAMERA_PATH "/dev/video"
#endif /* camera */

/* fixed value camera setting based on webcam */
#define BUF_SIZE    4096
#define COLR_CHAN   3
#define CAM_WIDTH   1280
#define CAM_HEIGHT  720
#define CAMERA_ID   0

/* pre-defined params */
#define LOW_THRESH      4
#define THRESH_RATIO    4
#define THRESH_KERNEL   5
#define BLUR_SIGMA      5
#define THRESH_MINVAL   127
#define THRESH_MAXVAL   255

typedef struct {
  char* camera;
  cv::Mat data;
}image;

/* main counter */
int img_counter   (cv::Mat input);
int img_get_frame (void);
