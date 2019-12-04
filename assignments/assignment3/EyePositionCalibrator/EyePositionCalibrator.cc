#include "computer-vision/assignments/assignment3/EyePositionCalibrator/EyePositionCalibrator.h"

namespace cv_project {
namespace assignment3 {

bool EyePositionCalibrator::DoCalibration() {
  cv::cvtColor(image_, gray_, CV_BGR2GRAY);
  cv::equalizeHist(gray_, gray_);

  cascade_classifier_.detectMultiScale(gray_, objects_, 1.1, 4,
                                       CV_HAAR_SCALE_IMAGE, {10, 10});

  int x1 = objects_.front().x + objects_.front().width / 2;
  int x2 = objects_.back().x + objects_.back().width / 2;
  int y1 = objects_.front().y + objects_.front().height / 2;
  int y2 = objects_.back().y + objects_.back().height / 2;

  if (objects_.size() == 2 && std::abs(y1 - y2) < 20 &&
      std::abs(x1 - x2) > 30 && std::abs(x1 - x2) < 70) {
    eyes_count_[input_name_]++;
    eye_center_ = std::to_string(x1) + " " + std::to_string(y1) + " " +
                  std::to_string(x2) + " " + std::to_string(y2);
    return true;
  } else {
    return false;
  }
}

}  // namespace assignment3
}  // namespace cv_project
