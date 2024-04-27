/* pre-define value for makefile */
#define VERSION   1
#define REVISION  1

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <fstream>

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
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/opencv_modules.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>


/* include for direct linking */
#include <opencv4/opencv2/core/core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#endif 

/* what function needs OpenMP ? */ 
#ifdef OMP
#include <omp.h>
#endif

/* check for local configuration file  */
extern "C" {
  int check_valid_file(char*);
  #include "parser.c"
};

/* colour */
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RST "\x1B[0m"

/* fixed value camera setting based on webcam */
#define BUF_SIZE    4096
#define COLR_CHAN   3
#define CAM_WIDTH   1280
#define CAM_HEIGHT  720
#define CAMERA_ID   0
#define CAMERA_PATH "/dev/video"

/* main counter */
int img_counter   (cv::Mat input);
int img_get_frame (void);
