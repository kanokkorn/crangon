/*
 *  no syscall with performance is acceptable
 *  TODO:
 *  - *BSD and Linux compatible headers
 *  - focus on clang features rather than GCC
 *  - downgrade OpenCV lib to 3.x for license to match project's license
 *  - test OpenCV version compatible
 *  - add UNIX domain socket & IPC for extension
 *  - test against glibc
 *  - test against musl
 *  - test against *BSD
 */

#define VERSION 1
#define REVISION 2
#define _DEFAULT_SOURCE

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <thread>
#include <cstdlib>
#include <cstdint>
#include <csignal>

#if defined(__linux__) || defined (__gnu_linux__)
#include <sys/types.h>
#include <sys/ipc.h>
/* currently OpenCV 4.7 dev, might switch to 3.x for BSD license */
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/cvstd_wrapper.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/video/background_segm.hpp>
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

#define BLUR_KERNEL 3
#define BLUR_SIGMA  2

#define LOW_THRESH    100
#define THRESH_RATIO    3
#define THRESH_KERNEL   3

