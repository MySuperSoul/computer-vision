#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT2_KEYPOINTSFINDER_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT2_KEYPOINTSFINDER_H_

#include <vector>

#include "computer-vision/assignments/common/renderer.h"
#include "opencv2/opencv.hpp"

namespace cv_project {
namespace assignment2 {

class KeyPointsFinder {
 public:
  explicit KeyPointsFinder(cv::Mat image) : image_(image) {}

  ~KeyPointsFinder() {
    cv::destroyAllWindows();
  }

  inline std::vector<std::vector<cv::Point>> GetContours() {
    FitGrayImage();
    FindContours();
    return contours_;
  }

 private:
  inline void FitGrayImage() {
    cv::cvtColor(image_, gray_image_, CV_BGR2GRAY);
    cv::GaussianBlur(gray_image_, gray_image_, cv::Size(3, 3), 11, 11);
  }

  void FindContours();

  cv::Mat image_;
  cv::Mat gray_image_;
  cv::Mat edge_image_;
  std::vector<std::vector<cv::Point>> contours_;
  std::unique_ptr<cv_common::Renderer> renderer_;
};
}  // namespace assignment2
}  // namespace cv_project
#endif
