#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT4_VIEW_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT4_VIEW_PROCESSOR_H_

#include <string>
#include <vector>

#include "computer-vision/assignments/common/util.h"
#include "opencv2/opencv.hpp"

namespace cv_project {
namespace assignment4 {

class BirdViewProcessor {
 public:
  explicit BirdViewProcessor(const std::string &image_path,
                             const std::string &intrinsic_xml_path)
      : image_path_(image_path), intrinsic_xml_path_(intrinsic_xml_path) {
    xml_input_.open(intrinsic_xml_path_, cv::FileStorage::READ);
    if (!xml_input_.isOpened()) {
      std::cerr << "Can not open " << intrinsic_xml_path_ << std::endl;
      std::exit(0);
    }

    image_ = cv::imread(image_path_, 1);
    if (!image_.data) {
      std::cerr << "Can not open input image " << image_path_ << std::endl;
      std::exit(0);
    }

    xml_input_["image_width"] >> image_width_;
    xml_input_["image_height"] >> image_height_;
    xml_input_["board_width"] >> board_width_;
    xml_input_["board_height"] >> board_height_;
    xml_input_["intrinsic_matrix"] >> intrinsic_matrix_;
    xml_input_["distortion_coeffs"] >> distortion_coeffs_;

    xml_input_.release();
  }

  ~BirdViewProcessor() {
    cv::destroyAllWindows();
  }

  void DoBirdViewTransform(bool with_undistort = false);

 private:
  inline void Preprocess(bool with_undistort) {
    if (with_undistort) {
      cv::undistort(image_, undistort_image_, intrinsic_matrix_,
                    distortion_coeffs_);
    } else {
      undistort_image_ = image_.clone();
    }
    cv::cvtColor(undistort_image_, gray_image_, CV_BGR2GRAY);
  }

  void FitPoints(cv::Point2f *object_points, cv::Point2f *image_points,
                 const std::vector<cv::Point2f> &corners);

  void ShowVectorValues(cv::Point2f *object_points, cv::Point2f *image_points);

 private:
  int board_width_, board_height_, image_width_, image_height_, win_size_{11};
  double bird_height_{20};
  std::string image_path_, intrinsic_xml_path_;
  cv::Mat intrinsic_matrix_, distortion_coeffs_, image_, gray_image_,
      undistort_image_, homography_;
  cv::FileStorage xml_input_;
};

}  // namespace assignment4
}  // namespace cv_project

#endif
