#include "crangc.hh"

int camera_number = 0;
cv::Ptr<cv::BackgroundSubtractor> bg_subtractor;

/* circle pipeline */
void circlepipe(cv::Mat inputimage) {
  cv::Mat gray;
  cv::cvtColor(inputimage, gray, cv::COLOR_BGR2GRAY);
  cv::Mat blurred;
  cv::GaussianBlur(gray, blurred, cv::Size(9, 9), 2, 2);
  std::vector<cv::Vec3f> circles;
  cv::HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, 1, blurred.rows / 8, 200, 100, 0, 0);
  for (size_t i = 0; i < circles.size(); i++) {
    cv::Vec3f c = circles[i];
    cv::Point center(cvRound(c[0]), cvRound(c[1]));
    int radius = cvRound(c[2]);
    circle(inputimage, center, 3, cv::Scalar(0, 255, 0), -1);
    circle(inputimage, center, radius, cv::Scalar(0, 0, 255), 2);
  }
  cv::imwrite("output.png", inputimage);
}


/* contour pipeline */
void contourpipe(cv::Mat inputimage) {
  cv::Mat gray;
  cv::cvtColor(inputimage, gray, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0);
  cv::Mat thresholded;
  cv::threshold(gray, thresholded, 0, 255, cv::THRESH_BINARY);
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(thresholded, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
  for (size_t i = 0; i < contours.size(); i++) {
    double area = contourArea(contours[i]);
    double radius = sqrt(area / CV_PI);
    if (radius < 100) {
      drawContours(inputimage, contours, (int)i, cv::Scalar(0, 255, 0), 2);
    }
  }
  cv::imwrite("output.png", inputimage);
} 

void server_mode(void) {
  /* start timer block */
  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
  spdlog::info("crangd daemon start @ {}", std::ctime(&start_time));
  spdlog::info("checking for connected camera(s)...");
  /* start timer block */

  /* end timer block */
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  spdlog::critical("daemon reached the of the line, please reboot the system");
  spdlog::critical("crangd has been running for {:03.2f}s since {}", 
      elapsed_seconds.count(), std::ctime(&start_time));
  /* end timer block */
} 

int main(void) {
  cv::Mat image = cv::imread("coins.jpg");
  if (image.empty()) {
    spdlog::error("could not open image.");
    return -1;
  }
  circlepipe(image);
  return 0;
}
