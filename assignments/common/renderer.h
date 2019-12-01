#ifndef COMPUTER_VISION_ASSIGNMENTS_COMMON_RENDERER_H_
#define COMPUTER_VISION_ASSIGNMENTS_COMMON_RENDERER_H_

#include <string>

#include "opencv2/opencv.hpp"

namespace cv_project {
namespace cv_common {

class Renderer {
 public:
  Renderer() = default;
  ~Renderer() {
    cv::destroyAllWindows();
  };

  inline void DrawEclipse(cv::Mat *image, const cv::RotatedRect &box,
                          const cv::Scalar &color, const int &thickness,
                          const int &line_type) {
    cv::ellipse(*image, box, color, thickness, line_type);
  }

  inline void ShowImage(const cv::Mat &image, const std::string &window_name) {
    cv::imshow(window_name, image);
  }
};

}  // namespace cv_common
}  // namespace cv_project

#endif
