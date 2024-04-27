/*
 * 	File: main.cc
 * 	written on Linux, designed to work on FreeBSD 13.x and later
 */

#include "crangc.hh"
#include <iostream>

/* const error message - */
const char* cam_error = "can't open camera or doesn't existed\n";
const char* config_error = "failed to parsing config file, make sure cranconfig is exists\n";
const char* check_cam = "checking camera\n";

/* cheap implement from Python version, not fine tuning yet */

int img_counter(cv::Mat input) {
  int total_unit = 0;
  cv::cvtColor(input, input, cv::COLOR_BGR2GRAY);
  cv::threshold(input, input, 128, 255, cv::THRESH_BINARY);
  std::vector<std::vector<cv::Point> > contours;
  cv::Mat contourOutput = input.clone();
  cv::findContours(contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
  cv::Mat contourImage(input.size(), CV_8UC3, cv::Scalar(0, 0, 0));
  
  cv::Scalar colors[3];
  colors[0] = cv::Scalar(255, 0, 0);
  colors[1] = cv::Scalar(0, 255, 0);
  colors[2] = cv::Scalar(0, 0, 255);
  for (size_t idx = 0; idx < contours.size(); idx++) {
    cv::drawContours(contourImage, contours, idx, colors[idx % 5]);
  }
  return total_unit;
}

/*
   read frame from camera input or video 
   refactor planned
*/
int img_get_frame(void) {
  cv::VideoCapture cap(CAMERA_ID, cv::CAP_ANY);
  if (!cap.isOpened()) {
    write(1, cam_error, sizeof(cam_error)-1);
    return 1;
  }
  cap.set(cv::CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT,CAM_HEIGHT);
  while (cap.isOpened()) {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
      std::cout << "got empty frame, breaking" << std::endl;
      break;
    }
    cv::imshow("normal output", frame);
    cv::imshow("process output", img_counter(frame));

    /* find better way to quit program */
    char q = (char)cv::waitKey(1);
    if (q == 27) {
      exit(EXIT_FAILURE);
    }
=======
/* 
 * TODO:
 *  - check camera avaliablity
 *  - check camera usability
 *  - read frame from camera continuious, while running create threads
 *      and pipe through UNIX Domain socket for image streaming to DISPLAY
 *  - do greyscale convertion
 *  - do gaussian filter for smooth image
 *  - apply canny edge
 *  - draw circle to image with contour function
 *  - counting method
 *  - return result value
 *
 * EXTRA:
 *  - spawn a thread for stream image data to frontend via UDS 
 *  - local storage and cache
 *  - 
 */

#include "main.hh"
#include <opencv4/opencv2/core/cvstd_wrapper.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/video/background_segm.hpp>

int camera_number = 0;
cv::Ptr<cv::BackgroundSubtractor> bg_subtractor;

/* checking USB with `lsusb` might not work with *BSD */
std::string camera_avalible(void) {
  char buf_size[256];
  std::string result = "";
  FILE *pipe = popen("lsusb", "r");
  if (!pipe) throw std::runtime_error("camera can't be check");
  try {
    while (fgets(buf_size, sizeof buf_size, pipe) != NULL) {
      result += buf_size;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  return result;
}

/* this function run forever, until machine is shutdown */
void read_frame(void) {
  cv::VideoCapture camera;
  camera.open(camera_number);
  while (true) {
    std::cout << "run forever til shutdown" << std::endl;
  }
}

/* Pre-processing before do contour
 * ported from old project, not test yet
 */
cv::Mat pre_process(cv::Mat raw_image) {
  cv::Mat processed, greyed, filtered, blured;
  cv::cvtColor(raw_image, greyed, cv::COLOR_RGB2GRAY);
  cv::GaussianBlur(greyed, blured, cv::Size(BLUR_KERNEL, BLUR_KERNEL), BLUR_SIGMA);
  cv::Canny(blured, processed, LOW_THRESH, LOW_THRESH*THRESH_RATIO, THRESH_KERNEL);
  return processed;
}

cv::Mat contour_draw(cv::Mat processed) {
  cv::Mat contoured = processed;
  return contoured;
}

/* 
 * counting contour using c++11 feature set
 * counting length of array element
 */
int32_t contour_count(cv::Mat contoured) {
  int32_t image_array[20];
  for (int32_t& idx: image_array) {
    std::cout << "counting\n";
  }
  return 0;
}

/* main function */
int main(void) {
  std::cout << "probing USB for avaliable camera...\n" << std::endl;
  local_db_avaliable();
  std::cout << camera_avalible() << std::endl;
  camera_usable();
  std::cout << "start reading frame from camera" << std::endl;
  return 0;
}
