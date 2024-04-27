#include "crangc.hh"
#include <opencv4/opencv2/core/cvstd_wrapper.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/video/background_segm.hpp>

int camera_number = 0;
cv::Ptr<cv::BackgroundSubtractor> bg_subtractor;

/* checking USB with `lsusb` might not work with *BSD */
std::string camera_avalible(void) {
  char buf_size[256];
  std::string result = "";
  FILE *pipe = popen("lsusb", "r");
  if (!pipe) throw std::runtime_error("camera can't be check");
  try {
    while (fgets(buf_size, sizeof buf_size, pipe) != NULL) {
      result += buf_size;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  return result;
}

/* this function run forever, until machine is shutdown */
void read_frame(void) {
  cv::VideoCapture camera;
  camera.open(camera_number);
  while (true) {
    std::cout << "run forever til shutdown" << std::endl;
  }
}

/* Pre-processing before do contour
 * ported from old project, not test yet
 */
cv::Mat pre_process(cv::Mat raw_image) {
  cv::Mat processed, greyed, filtered, blured;
  cv::cvtColor(raw_image, greyed, cv::COLOR_RGB2GRAY);
  cv::GaussianBlur(greyed, blured, cv::Size(SI_KERNEL, SI_KERNEL), BLUR_SIGMA);
  cv::Canny(blured, processed, LOW_THRESH, LOW_THRESH*THRESH_RATIO, THRESH_KERNEL);
  return processed;
}

cv::Mat contour_draw(cv::Mat processed) {
  cv::Mat contoured = processed;
  return contoured;
}

/* 
 * counting contour using c++11 feature set
 * counting length of array element
 */
int32_t contour_count(cv::Mat contoured) {
  int32_t image_array[20];
  for (int32_t& idx: image_array) {
    std::cout << "counting\n";
  }
  return 0;
}

/* main function */
int main(void) {
  std::cout << "probing USB for avaliable camera...\n" << std::endl;
  std::cout << camera_avalible() << std::endl;
  camera_avalible();
  std::cout << "start reading frame from camera" << std::endl;
  return 0;
}
