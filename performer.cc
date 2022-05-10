#include "main.hh"

void performer(void) {
  spdlog::info("spawning performer");
  cv::Mat frame;
  while (true) {
    spdlog::info("performer haven't received any task from director");
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  };
}

uint16_t counter(cv::Mat input_img) {
  cv::Mat blur, edge;
  /*
   * input -> blur -> filter -> canny -> thresh -> contour -> count
   */
  //cv::GaussianBlur(input_img, blur, cv::Size(3, 3), 0, 0);
  //blur = cv::bilateralFilter(blur);
  //cv::Canny(blur, edge, 100, 200, 3, false);
  return 0;
}
