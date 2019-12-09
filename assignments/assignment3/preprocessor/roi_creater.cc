#include "computer-vision/assignments/assignment3/preprocessor/roi_creater.h"

namespace cv_project {
namespace assignment3 {

void RoiCreater::ReadValues(const std::string &input_path,
                            std::vector<int *> value_ptrs) {
  mask_input_.open(input_path, std::ios::out);
  if (!mask_input_.is_open()) {
    std::cerr << "Can not open file: " << input_path << std::endl;
    return;
  }

  std::string s;
  std::getline(mask_input_, s);

  auto values = cv_common::Util::SplitStrToVector(s);
  *value_ptrs[0] = std::stoi(values[0]);
  *value_ptrs[1] = std::stoi(values[1]);
  *value_ptrs[2] = std::stoi(values[2]);
  *value_ptrs[3] = std::stoi(values[3]);

  mask_input_.close();
}

void RoiCreater::ReadEyePosition() {
  std::vector<int *> value_ptrs{&eye_x1_, &eye_y1_, &eye_x2_, &eye_y2_};
  std::string eye_path = cv_common::Util::ReplacePostFix(frame_path_, "txt");
  ReadValues(eye_path, value_ptrs);
}

cv::Mat RoiCreater::GetFaceRoiFrame() {
  ReadEyePosition();
  if (eye_x1_ > eye_x2_) {
    std::swap(eye_x1_, eye_x2_);
    std::swap(eye_y1_, eye_y2_);
  }

  cv::Point center((eye_x1_ + eye_x2_) / 2, (eye_y1_ + eye_y2_) / 2);
  double angle = std::atan((eye_y2_ - eye_y1_) * 1.0 / (eye_x2_ - eye_x1_)) *
                 180.0 / CV_PI;
  auto trans_matrix = cv::getRotationMatrix2D(center, angle, 1.0);
  cv::Mat rotate_frame;
  cv::warpAffine(frame_, rotate_frame, trans_matrix, frame_.size());

  return rotate_frame;
}

}  // namespace assignment3
}  // namespace cv_project
