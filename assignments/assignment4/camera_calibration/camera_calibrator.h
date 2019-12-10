#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT4_CAMERA_CALIBRATION_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT4_CAMERA_CALIBRATION_H_

#include <string>
#include <vector>

#include "computer-vision/assignments/common/util.h"
#include "opencv2/opencv.hpp"

namespace cv_project {
namespace assignment4 {

#define AINFO(x) std::cout << (x) << std::endl;

class CameraCalibrator {
 public:
  explicit CameraCalibrator(const int &board_width, const int &board_height,
                            const int &num_boards, const double &image_scale,
                            const std::string &data_prefix,
                            const std::string &intrinsic_xml_path)
      : board_width_(board_width),
        board_height_(board_height),
        num_boards_(num_boards),
        image_scale_(image_scale),
        data_prefix_(data_prefix),
        intrinsic_xml_path_(intrinsic_xml_path) {
    image_paths_ = cv_common::Util::GetAllImagePaths(data_prefix_);
    FitPoints();
  }

  ~CameraCalibrator() {
    cv::destroyAllWindows();
  }

  void DoCalibration();

  void ShowUndistortImages();

 private:
  void FitPoints();

 private:
  int board_width_, board_height_, num_boards_, image_width_, image_height_;
  double image_scale_;
  std::string data_prefix_, intrinsic_xml_path_;
  cv::FileStorage xml_output_;

  // privide points storage
  std::vector<std::vector<cv::Point2f>> image_points_;
  std::vector<std::vector<cv::Point3f>> object_points_;

  // vector to store calibration image paths
  std::vector<cv::String> image_paths_;
  cv::Mat intrinsic_matrix_, distortion_coeffs_;
};

}  // namespace assignment4
}  // namespace cv_project

#endif
