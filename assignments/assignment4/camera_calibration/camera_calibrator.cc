#include "computer-vision/assignments/assignment4/camera_calibration/camera_calibrator.h"

namespace cv_project {
namespace assignment4 {

void CameraCalibrator::FitPoints() {
  for (size_t i = 0; (i < image_paths_.size() && i < num_boards_); i++) {
    cv::Mat image_tmp, image = cv::imread(image_paths_[i]);
    if (!image.data) {
      std::cerr << "File " << image_paths_[i] << " is not a image."
                << std::endl;
      continue;
    }
    image_width_ = image.cols;
    image_height_ = image.rows;

    cv::resize(image, image_tmp,
               {static_cast<int>(image.cols * image_scale_),
                static_cast<int>(image.rows * image_scale_)});
    cv::cvtColor(image_tmp, image_tmp, CV_BGR2GRAY);

    // find the corners
    std::vector<cv::Point2f> corners;
    bool found = cv::findChessboardCorners(
        image_tmp, {board_width_, board_height_}, corners);
    cv::drawChessboardCorners(image, {board_width_, board_height_}, corners,
                              found);

    if (found) {
      image ^= cv::Scalar::all(255);

      for (auto &point : corners) {
        point.x *= (1.0 / image_scale_);
        point.y *= (1.0 / image_scale_);
      }

      image_points_.push_back(corners);
      object_points_.push_back(std::vector<cv::Point3f>());
      auto &opts = object_points_.back();
      opts.resize(board_width_ * board_height_);

      // fit objects 3d coordinates
      for (int j = 0; j < board_height_ * board_width_; j++) {
        opts[j] = cv::Point3f(static_cast<float>(j / board_width_),
                              static_cast<float>(j % board_width_), 0.0);
      }
    }
  }
  AINFO("Fit Points Done");
}

void CameraCalibrator::DoCalibration() {
  xml_output_.open(intrinsic_xml_path_, cv::FileStorage::WRITE);

  double error = cv::calibrateCamera(
      object_points_, image_points_, {image_width_, image_height_},
      intrinsic_matrix_, distortion_coeffs_, cv::noArray(), cv::noArray(),
      cv::CALIB_ZERO_TANGENT_DIST | cv::CALIB_FIX_PRINCIPAL_POINT);
  AINFO("Done calibration. Reprojection error is " + std::to_string(error));

  xml_output_ << "image_width" << image_width_ << "image_height"
              << image_height_ << "board_width" << board_width_
              << "board_height" << board_height_ << "intrinsic_matrix"
              << intrinsic_matrix_ << "distortion_coeffs" << distortion_coeffs_;
  xml_output_.release();
}

void CameraCalibrator::ShowUndistortImages() {
  cv::Mat map1, map2;
  cv::initUndistortRectifyMap(intrinsic_matrix_, distortion_coeffs_, cv::Mat(),
                              intrinsic_matrix_, {image_width_, image_height_},
                              CV_16SC2, map1, map2);

  for (const auto &path : image_paths_) {
    cv::Mat image, image_tmp = cv::imread(path);
    cv::remap(image_tmp, image, map1, map2, cv::INTER_LINEAR,
              cv::BORDER_CONSTANT, cv::Scalar());
    cv::resize(image, image,
               {static_cast<int>(image.cols * 0.5),
                static_cast<int>(image.rows * 0.5)});
    cv::resize(image_tmp, image_tmp,
               {static_cast<int>(image_tmp.cols * 0.5),
                static_cast<int>(image_tmp.rows * 0.5)});
    cv::imshow("Origin", image_tmp);
    cv::imshow("Undistort", image);
    cv::waitKey(0);
  }
}

}  // namespace assignment4
}  // namespace cv_project
