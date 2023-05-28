/*
 * 	File: main.cc
 * 	Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 * 	consider rewrite to be usable next merge
 */

#include "main.hh"

/* error message - */
const char* cam_error = "can't open camera\n";
const char* config_error = "failed to load config file\n";
const char* check_cam = "checking camera\n";

/* contour and return counting number */
cv::Mat img_counter(cv::Mat input) {
  cv::cvtColor(input, input, cv::COLOR_BGR2GRAY);
  cv::threshold(input, input, 128, 255, cv::THRESH_BINARY);
  std::vector<std::vector<cv::Point> > contours;
  cv::Mat contourOutput = input.clone();
  cv::findContours( contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
  cv::Mat contourImage(input.size(), CV_8UC3, cv::Scalar(0, 0, 0));
  cv::Scalar colors[3];
  colors[0] = cv::Scalar(255, 0, 0);
  colors[1] = cv::Scalar(0, 255, 0);
  colors[2] = cv::Scalar(0, 0, 255);
  for (size_t idx = 0; idx < contours.size(); idx++) {
    cv::drawContours(contourImage, contours, idx, colors[idx % 5]);
  }
  return contourImage;
}

/* read frame from camera input or video */
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
    char q = (char)cv::waitKey(1);
    if (q == 27)
      break;
  }
  cv::destroyAllWindows();
  return 0;
}

/* if got SIGINT or throw error, tell overwatch to restart again
 * reserved for actual hardware
 */
#if defined(__aarch64__) || defined(_M_ARM64)
void int_handler(int signum) {
  _exit(signum);
}
#endif

int main(int argc, char** argv) {
  char *c;
  write(1, cam_error, strlen(cam_error));
  std::ifstream ifs("config_file");
  if (ifs.fail()) {
    write(1, config_error, strlen(config_error));
    exit(-1);
  }
  write(1, check_cam, strlen(check_cam));
  /* read image from camera */
  cv::Mat img_zero;
  img_zero = cv::Mat::zeros(1, 1, CV_64F);
  exit(1);
}
