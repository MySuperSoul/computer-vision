#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_PREPROCESSOR_ROI_CREATER_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_PREPROCESSOR_ROI_CREATER_H_

#include <iostream>
#include <string>

#include "computer-vision/assignments/common/util.h"
#include "opencv2/opencv.hpp"

namespace cv_project {
namespace assignment3 {

class RoiCreater {
 public:
  explicit RoiCreater() {
    ReadMask();
  }
  explicit RoiCreater(const std::string &mask) : mask_(mask) {
    ReadMask();
  }

  ~RoiCreater() {}

  inline void SetImagePath(const std::string &frame_path) {
    frame_path_ = frame_path;
    frame_ = cv::imread(frame_path_);
  }

  cv::Mat GetFaceRoiFrame();

 private:
  void ReadValues(const std::string &input_path, std::vector<int *> values);
  void ReadMask();
  void ReadEyePosition();

  int xdiff_, ydiff_, height_, width_;
  int eye_x1_, eye_x2_, eye_y1_, eye_y2_;
  cv::Mat frame_;
  cv::Mat roi_frame_;
  std::ifstream mask_input_;
  std::string mask_{
      "/home/huangyifei/computer-vision/assignments/assignment3/Mask/mask.txt"};
  std::string frame_path_;
};

}  // namespace assignment3
}  // namespace cv_project

#endif
