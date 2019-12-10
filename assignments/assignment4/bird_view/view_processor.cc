#include "computer-vision/assignments/assignment4/bird_view/view_processor.h"

namespace cv_project {
namespace assignment4 {
void BirdViewProcessor::FitPoints(cv::Point2f *object_points,
                                  cv::Point2f *image_points,
                                  const std::vector<cv::Point2f> &corners) {
  object_points[0].x = 0;
  object_points[0].y = 0;
  object_points[1].x = board_width_ - 1;
  object_points[1].y = 0;
  object_points[2].x = 0;
  object_points[2].y = board_height_ - 1;
  object_points[3].x = board_width_ - 1;
  object_points[3].y = board_height_ - 1;

  image_points[0] = corners[0];
  image_points[1] = corners[board_width_ - 1];
  image_points[2] = corners[(board_height_ - 1) * board_width_];
  image_points[3] = corners[board_height_ * board_width_ - 1];
}

void BirdViewProcessor::DoBirdViewTransform(bool with_undistort) {
  Preprocess(with_undistort);
  std::vector<cv::Point2f> corners;
  bool found = cv::findChessboardCorners(
      gray_image_, {board_width_, board_height_}, corners,
      cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);

  // refine the corners found
  cv::cornerSubPix(
      gray_image_, corners, {win_size_, win_size_}, {-1, -1},
      cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 30,
                       0.1));

  cv::drawChessboardCorners(undistort_image_, {board_width_, board_height_},
                            corners, found);
  cv::Point2f object_points[4], image_points[4];
  FitPoints(object_points, image_points, corners);

  cv::Mat homography = cv::getPerspectiveTransform(object_points, image_points);

  cv::Mat image_tmp;
  cv::resize(undistort_image_, image_tmp,
             {static_cast<int>(undistort_image_.cols * 0.5),
              static_cast<int>(undistort_image_.rows * 0.5)});
  cv::imshow("Undistort", image_tmp);

  homography.at<double>(2, 2) = bird_height_;
  cv::warpPerspective(undistort_image_, image_, homography,
                      undistort_image_.size(),
                      cv::WARP_INVERSE_MAP | cv::INTER_LINEAR,
                      cv::BORDER_CONSTANT, cv::Scalar::all(0));
  cv::resize(image_, image_,
             {static_cast<int>(image_.cols * 0.5),
              static_cast<int>(image_.rows * 0.5)});
  cv::imshow("BirdEye", image_);
  cv::waitKey(0);
}

}  // namespace assignment4
}  // namespace cv_project
