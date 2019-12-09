#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_EYEPOSITIONCALIBRATOR_EYEPOSITIONCALIBRATOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_EYEPOSITIONCALIBRATOR_EYEPOSITIONCALIBRATOR_H_

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "opencv2/opencv.hpp"

namespace cv_project {
namespace assignment3 {

class EyePositionCalibrator {
 public:
  EyePositionCalibrator() {
    cascade_classifier_.load(cascade_name_);
    if (cascade_classifier_.empty()) {
      std::cerr << "Not load cascade_classifier_" << std::endl;
      return;
    }
  }

  ~EyePositionCalibrator() {
    cv::destroyAllWindows();
  }

  inline void SetImage(const std::string &input_name, const std::string &name) {
    input_name_ = input_name;
    image_ = cv::imread(input_name_);
    input_name_ = name;
  }

  inline std::string GetEyeCenter() {
    return eye_center_;
  }

  bool DoCalibration();

 private:
  cv::Mat image_;
  cv::Mat gray_;
  std::string input_name_;
  std::string eye_center_;
  std::unordered_map<std::string, int> eyes_count_;
  std::vector<cv::Rect> objects_;
  cv::CascadeClassifier cascade_classifier_;
  cv::String cascade_name_{
      "/usr/local/opencv-3.3.1/share/OpenCV/haarcascades/"
      "haarcascade_eye_tree_eyeglasses.xml"};
};
}  // namespace assignment3
}  // namespace cv_project

#endif
