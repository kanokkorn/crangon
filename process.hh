#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <spdlog/spdlog.h>

typedef struct {
  uint8_t vid_id;
  uint16_t vid_width;
  uint16_t vid_height;
  std::string vid_path;
}vid_conf;

typedef struct {
  uint32_t real_out;
  uint32_t average;
  int32_t computer_buf;
  int32_t computer_now;
}output_data;

cv::Mat img_counter(cv::Mat input);
int img_get_frame(uint8_t cam_id, uint8_t vid_width, uint8_t vid_height);

