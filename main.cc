/*
 * File: main.cc
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#include "main.hh"

/* contour and return counting number */

cv::Mat imgproc(cv::Mat input) {
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

int get_frame(uint8_t cam_id, uint8_t vid_width, uint8_t vid_height) {
  cv::VideoCapture cap(cam_id, cv::CAP_ANY);
  if (!cap.isOpened()) {
    spdlog::critical("can't open selected camera");
    return 1;
  }
  cap.set(cv::CAP_PROP_FRAME_WIDTH, vid_width);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT,vid_height);
  while (cap.isOpened()) {
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
  }
  cv::destroyAllWindows();
  return 0;
}

/* CTRL + C handler */

void sig_handler(int signum) {
  if (signum == 2) {
    spdlog::critical("interrupt received. exit\n");
    stop = 1;
    exit(signum);
  } else if (signum == 20) {
    spdlog::critical("terminal stop. pausing for 30 sec\n");
    sleep(30);
    spdlog::critical("timer expired. countinuing\n");
  }
}

int main(void) {
  vid_conf *vidf = new vid_conf;
  signal(SIGINT, sig_handler);
  signal(SIGTSTP, sig_handler);
  spdlog::info("running OpenCV version: {}", CV_VERSION);
  spdlog::info("parsing config.json");
  std::ifstream ifs("config.json");
  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);
  if (ifs.fail()) {
    spdlog::critical("error -> exit, config.json not found!");
    exit(1);
  }
  spdlog::info("SERIAL: {}", obj["device_serial"].asString());
  if (obj["enable_cam"].asBool()) {
    vidf->vid_id = obj["camera_id"].asUInt();
    spdlog::info("Camera Model: {0:d}", vidf->vid_id);
    try {
      auto camera = std::async(
          get_frame,
          vidf->vid_id,
          vidf->vid_width,
          vidf->vid_height
          );
    }
    catch (cv::Exception& e) {
      spdlog::warn("cannot open camera: {}", obj["video"].asString());
    }
  } else {
    spdlog::warn(
        "enable_cam is set to false, crangon will use video path instead: {}",
        obj["video"].asString()
        );
    vidf->vid_path = obj["camera_id"].asString();
  }
  return 0;
}
