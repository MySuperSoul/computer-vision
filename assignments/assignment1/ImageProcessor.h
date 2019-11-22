#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT1_IMAGE_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT1_IMAGE_PROCESSOR_H_

#include <ctime>
#include <opencv2/opencv.hpp>
#include <vector>

namespace cv_project {
namespace assignment1 {

class ImageProcessor {
 public:
  ImageProcessor() = default;
  ~ImageProcessor() = default;

  void GetConcatImages(const cv::Mat &last_frame, const cv::Mat &current_frame,
                       std::vector<cv::Mat> *concat_images);

  void SlowlyChangeThroughImages(std::vector<cv::Mat> *concat_images);

  void ShiftFromRight(std::vector<cv::Mat> *concat_images);

  void ShiftFromLeft(std::vector<cv::Mat> *concat_images);

  void ExpandFromMiddle(std::vector<cv::Mat> *concat_images);

  void SetValues(const cv::Mat &last_frame, const cv::Mat &current_frame);

 private:
  cv::Mat last_frame_;
  cv::Mat current_frame_;
  cv::Mat image_;

  int rand_index_;
  int cols_, rows_;
  int per_iter_;
  int per_iter_x_, per_iter_y_;
  int center_x_, center_y_;
};

}  // namespace assignment1
}  // namespace cv_project
#endif
