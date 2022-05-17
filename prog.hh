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
    cv::imshow("output", frame);
    char q = (char)cv::waitKey(1);
    if (q==27)
      break;
    cv::destroyAllWindows();
  }
}

/* TODO: add image processing method */
cv::Mat imgproc(cv::Mat input) {
  cv::Mat blur, edge, post;
  cv::GaussianBlur(input, blur, cv::Size(3, 3), 0, 0);
  cv::bilateralFilter(blur, blur, 2, 2*2, 2/2);
  cv::Canny(blur, edge, 100, 200, 3, false);
  return edge;
}

#endif /* __PROG_H__ */
