#include "computer-vision/assignments/assignment1/ImageProcessor.h"

#include "computer-vision/assignments/common/util.h"

namespace cv_project {
namespace assignment1 {

namespace {
int kstore = 20;
int kfunc_num = 4;
}  // namespace

void ImageProcessor::SetValues(const cv::Mat &last_frame,
                               const cv::Mat &current_frame) {
  last_frame_ = last_frame;
  current_frame_ = current_frame;
  rows_ = last_frame_.rows;
  cols_ = last_frame_.cols;
  center_x_ = cols_ / 2;
  center_y_ = rows_ / 2;
  per_iter_ = cols_ / kstore;
  per_iter_x_ = per_iter_ / 2;
  per_iter_y_ = rows_ / (2 * kstore);
  image_ = cv::Mat::ones(rows_, cols_, CV_8UC3);
}

void ImageProcessor::SlowlyChangeThroughImages(
    std::vector<cv::Mat> *concat_images) {
  double weight;
  for (int i = 1; i <= kstore; i++) {
    weight = i * 1.0 / kstore;
    cv::addWeighted(last_frame_, 1 - weight, current_frame_, weight, 0.0,
                    image_);
    concat_images->push_back(image_.clone());
  }
}

void ImageProcessor::ShiftFromLeft(std::vector<cv::Mat> *concat_images) {
  for (int i = 0; i < kstore; i++) {
    int start_pos = i * per_iter_ + 1;
    int end_pos = std::min(start_pos + per_iter_, cols_);
    current_frame_.colRange(start_pos, end_pos)
        .copyTo(image_.colRange(start_pos, end_pos));
    concat_images->push_back(image_.clone());
  }
}

void ImageProcessor::ShiftFromRight(std::vector<cv::Mat> *concat_images) {
  for (int i = 0; i < kstore; i++) {
    int end_pos = std::min(cols_, cols_ - i * per_iter_ + 1);
    int start_pos = std::max(0, end_pos - per_iter_);
    current_frame_.colRange(start_pos, end_pos)
        .copyTo(image_.colRange(start_pos, end_pos));
    concat_images->push_back(image_.clone());
  }
}

void ImageProcessor::ExpandFromMiddle(std::vector<cv::Mat> *concat_images) {
  for (int i = 1; i <= kstore; i++) {
    int x = center_x_ - per_iter_x_ * i, y = center_y_ - per_iter_y_ * i;
    current_frame_(cv::Rect(x, y, 2 * i * per_iter_x_, 2 * i * per_iter_y_))
        .copyTo(
            image_(cv::Rect(x, y, 2 * i * per_iter_x_, 2 * i * per_iter_y_)));
    concat_images->push_back(image_.clone());
  }
}

void ImageProcessor::GetConcatImages(const cv::Mat &last_frame,
                                     const cv::Mat &current_frame,
                                     std::vector<cv::Mat> *concat_images) {
  SetValues(last_frame, current_frame);

  rand_index_ = cv_common::Util::GetRandNum(1, kfunc_num);
  switch (rand_index_) {
    case 1:
      SlowlyChangeThroughImages(concat_images);
      break;
    case 2:
      ShiftFromLeft(concat_images);
      break;
    case 3:
      ShiftFromRight(concat_images);
      break;
    case 4:
      ExpandFromMiddle(concat_images);
      break;
    default:
      return;
  }
}

}  // namespace assignment1
}  // namespace cv_project
