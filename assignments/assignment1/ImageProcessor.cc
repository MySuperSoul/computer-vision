#include "computer-vision/assignments/assignment1/ImageProcessor.h"

namespace cv_project {
namespace assignment1 {

namespace {
int kstore = 20;
}

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

void ImageProcessor::GetConcatImages(const cv::Mat &last_frame,
                                     const cv::Mat &current_frame,
                                     std::vector<cv::Mat> *concat_images) {
  SlowlyChangeThroughImages(last_frame, current_frame, concat_images);
  ShiftFromLeft(last_frame, current_frame, concat_images);
  ShiftFromRight(last_frame, current_frame, concat_images);
}

}  // namespace assignment1
}  // namespace cv_project
