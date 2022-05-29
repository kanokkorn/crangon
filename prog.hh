/*
 * File: prog.hh
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#ifndef __PROG_H__
#define __PROG_H__

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <spdlog/spdlog.h>

cv::Mat imgproc(cv::Mat);
int counter(cv::Mat);

void get_frame(uint8_t cam_id, uint8_t vid_width, uint8_t vid_height) {
  cv::VideoCapture cap(cam_id, cv::CAP_ANY);
  /* TODO: never shutdown even if no camera */
  if (!cap.isOpened()) {
    spdlog::critical("can't open selected camera");
    exit(1);
  }
  cap.set(cv::CAP_PROP_FRAME_WIDTH, vid_width);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT,vid_height);
#ifdef USE_VID
void get_frame(char** video_file) {
  VideoCapture cap(video_file);
  if (!cap.isOpened()) {
    spdlog::critical("can't open video file");
    exit(1);
  }
#endif /* USE_VID */
  while (true) {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
      spdlog::critical("got empty frame, breaking");
      break;
    }
    cv::imshow("normal output", frame);
    cv::imshow("process output", imgproc(frame));
    char q = (char)cv::waitKey(1);
    if (q==27)
      break;
    cv::destroyAllWindows();
  }
}

/* Solution from https://stackoverflow.com/question/8449378 */
cv::Mat imgproc(cv::Mat input) {
  cv::cvtColor(input, input, cv::COLOR_BGR2GRAY);
  cv::threshold(input, input, 128, 255, cv::THRESH_BINARY);
  std::vector<std::vector<cv::Point> > contours;
  cv::Mat contourOutput = input.clone();
  cv::findContours( contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
  /* Draw contours */
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

int counter(cv::Mat contourImage) {

}

#endif /* __PROG_H__ */
