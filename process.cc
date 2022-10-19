#include "process.hh"

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

int img_get_frame(uint8_t cam_id, uint8_t vid_width, uint8_t vid_height) {
  cv::VideoCapture cap(cam_id, cv::CAP_ANY);
  if (!cap.isOpened()) {
    std::cout << "cant open camera" << std::endl;
    return 1;
  }
  cap.set(cv::CAP_PROP_FRAME_WIDTH, vid_width);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT,vid_height);
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
    if (q==27)
      break;
  }
  cv::destroyAllWindows();
  return 0;
}

