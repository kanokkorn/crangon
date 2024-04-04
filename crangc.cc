/*
 * 	File: main.cc
 *  Author: kanokkorn kornkankit <kanokorn@outlook.jp>
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
  }
  cv::destroyAllWindows();
  return 0;
}

/* 
 *   TODO:
 *   - daemonise this program into `crangd`
 *   - config to run on start up boot
 *   - waiting client to connect to socket UDS or TCP
 *   - 
 */

int main(int argc, char** argv) {
  // std::cout << "crangc" << GRN + VERSION + RST << "is starting up" << BLU + PLATFORM + RST<< std::endl;
  // platform independent code
  write(1, cam_error, strlen(cam_error));
  std::ifstream ifs("cranconfig");
  if (ifs.fail()) {
    write(1, config_error, strlen(config_error));
    exit(EXIT_FAILURE);
  }
  write(1, check_cam, strlen(check_cam));
  /* read image from camera */
  cv::Mat img_zero;
  img_zero = cv::Mat::zeros(1, 1, CV_64F);
  exit(1);
}
