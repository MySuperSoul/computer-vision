#include "computer-vision/assignments/assignment1/ImageProcessor.h"

#include "computer-vision/assignments/common/util.h"

namespace cv_project {
namespace assignment1 {

namespace {
int kstore = 20;
int kfunc_num = 4;
}  // namespace

void ImageProcessor::SlowlyChangeThroughImages(
    const cv::Mat &last_frame, const cv::Mat &current_frame,
    std::vector<cv::Mat> *concat_images) {
  double weight;
  for (int i = 1; i <= kstore; i++) {
    weight = i * 1.0 / kstore;
    cv::Mat image;
    cv::addWeighted(last_frame, 1 - weight, current_frame, weight, 0.0, image);
    concat_images->push_back(image);
  }
}

void ImageProcessor::ShiftFromLeft(const cv::Mat &last_frame,
                                   const cv::Mat &current_frame,
                                   std::vector<cv::Mat> *concat_images) {
  int cols = last_frame.cols;
  int per_iter = cols / kstore;
  cv::Mat image = cv::Mat::ones(last_frame.rows, last_frame.cols, CV_8UC3);
  for (int i = 0; i < kstore; i++) {
    int start_pos = i * per_iter + 1;
    int end_pos = std::min(start_pos + per_iter, cols);
    current_frame.colRange(start_pos, end_pos)
        .copyTo(image.colRange(start_pos, end_pos));
    concat_images->push_back(image);
  }
}

void ImageProcessor::ShiftFromRight(const cv::Mat &last_frame,
                                    const cv::Mat &current_frame,
                                    std::vector<cv::Mat> *concat_images) {
  int cols = last_frame.cols;
  int per_iter = cols / kstore;
  cv::Mat image = cv::Mat::ones(last_frame.rows, last_frame.cols, CV_8UC3);
  for (int i = 0; i < kstore; i++) {
    int end_pos = std::min(cols, cols - i * per_iter + 1);
    int start_pos = std::max(0, end_pos - per_iter);
    current_frame.colRange(start_pos, end_pos)
        .copyTo(image.colRange(start_pos, end_pos));
    concat_images->push_back(image);
  }
}

void ImageProcessor::ExpandFromMiddle(const cv::Mat &last_frame,
                                      const cv::Mat &current_frame,
                                      std::vector<cv::Mat> *concat_images) {
  int cols = last_frame.cols, rows = last_frame.rows;
  int center_x = cols / 2, center_y = rows / 2;
  int per_iter_x = cols / (2 * kstore), per_iter_y = rows / (2 * kstore);

  cv::Mat image = cv::Mat::ones(last_frame.rows, last_frame.cols, CV_8UC3);
  for (int i = 1; i <= kstore; i++) {
    int x = center_x - per_iter_x * i, y = center_y - per_iter_y * i;
    last_frame(cv::Rect(x, y, 2 * i * per_iter_x, 2 * i * per_iter_y))
        .copyTo(image(cv::Rect(x, y, 2 * i * per_iter_x, 2 * i * per_iter_y)));
    concat_images->push_back(image);
  }
}

void ImageProcessor::GetConcatImages(const cv::Mat &last_frame,
                                     const cv::Mat &current_frame,
                                     std::vector<cv::Mat> *concat_images) {
  srand(static_cast<unsigned>(std::time(nullptr)));
  rand_index_ = cv_common::Util::GetRandNum(1, kfunc_num);
  std::cout << rand_index_ << std::endl;
  switch (rand_index_) {
    case 1:
      SlowlyChangeThroughImages(last_frame, current_frame, concat_images);
      break;
    case 2:
      ShiftFromLeft(last_frame, current_frame, concat_images);
      break;
    case 3:
      ShiftFromRight(last_frame, current_frame, concat_images);
      break;
    case 4:
      ExpandFromMiddle(last_frame, current_frame, concat_images);
      break;
    default:
      return;
  }
}

}  // namespace assignment1
}  // namespace cv_project
