/*
 * File: prog.hh
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#ifndef __PROG_H__
#define __PROG_H__

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

void get_frame(uint8_t cam_id) {
  VideoCapture cap(cam_id, cv::CAP_ANY);
  if (!cap.isOpened()) {
    spdlog::critical("can't open selected camera");
    exit(1);
  }
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
    cv::imshow("output", frame);
    char q = (char)cv::waitKey(1);
    if (q==27)
      break;
    cv::destroyAllWindows();
  }
}

cv::Mat imgproc(cv::Mat input) {
  /* TODO: add image processing method */
}

#endif /* __PROG_H__ */
