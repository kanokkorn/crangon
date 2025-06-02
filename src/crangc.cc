#include "crangc.hh"

/* TODO: new architecture
    - have 2 mode - cli and server
                  | cli : output as file
                  | server : start server and send image through UDS/TCP/UDP
    - write history, setting, log to sqlite database
    - config file - easiest way to adjust image processing pipeline
    - buffer & multithread - performance-oriented for embed devices
    - minimalism - required a few dependencies
 */

/* parameter */
int   default_camera  = 0;
char* camera_number   = 0;
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

void showversion(void) {
  std::cout << "crangc - aquatic computer vision\n" 
    << "build with OpenCV : " << CV_VERSION
    << std::endl;
}

void help_mesg(void) {
  std::cout << "Usage: ./crangon [options]\n"
    << "\nOptions:\n"
    << "  -h, --help           Show this help message and exit\n"
    << "  -s, --serve            Run server mode\n"
    << "  -t, --test             Perform self-test\n"
    << "  -f <file>, --file <file>\n"
    << "                       Specify input image\n"
    << "  -v, --verbose        Enable verbose output\n"
    << "  --version            Show program version\n"
    << std::endl;
}

cv::Mat generateRandomCirclesImage(int width = 1280, int height = 720) {
  cv::Mat image(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> numCirclesDist(10, 50); // Number of circles
  std::uniform_int_distribution<int> radiusDist(10, 100);    // Radius of circles
  std::uniform_int_distribution<int> xDist(0, width - 1);
  std::uniform_int_distribution<int> yDist(0, height - 1);
  std::uniform_int_distribution<int> colorDist(0, 255);

  int numCircles = numCirclesDist(rng);
  for (int i = 0; i < numCircles; ++i) {
    cv::Point center(xDist(rng), yDist(rng));
    int radius = radiusDist(rng);
    cv::Scalar color(colorDist(rng), colorDist(rng), colorDist(rng)); // Random BGR color
    cv::circle(image, center, radius, color, -1); // -1 means filled circle
  }
  return image;
}

void selftest(void) {
  cv::Mat image = generateRandomCirclesImage();
  if (image.empty()) {
    spdlog::error("could not open image.");
    exit(-1);
  }
  circlepipe(image);
  contourpipe(image);
}

void argcheck(char* args) {
  std::string arg = args;
  if (arg == "-h" || arg == "--help") {
    help_mesg();
  } if (arg == "-t" || arg == "--test") {
    selftest();
  } if (arg == "-f" || arg == "--file") {
    help_mesg();
  } if (arg == "-s" || arg == "--serve") {
    server_mode();
  } if (arg == "--version") {
    showversion();
  }
}

int main(int argc, char** argv) {
  argc <= 1 ? help_mesg() : argcheck(argv[1]);
  // cv::Mat image = cv::imread("coins.jpg");
  // if (image.empty()) {
  //   spdlog::error("could not open image.");
  //   return -1;
  // }
  // circlepipe(image);
  // contourpipe(image);
  return 0;
}
