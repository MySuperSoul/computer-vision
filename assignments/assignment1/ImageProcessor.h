#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT1_IMAGE_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT1_IMAGE_PROCESSOR_H_

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

  void SlowlyChangeThroughImages(const cv::Mat &last_frame,
                                 const cv::Mat &current_frame,
                                 std::vector<cv::Mat> *concat_images);
  void ShiftFromRight(const cv::Mat &last_frame, const cv::Mat &current_frame,
                      std::vector<cv::Mat> *concat_images);

  void ShiftFromLeft(const cv::Mat &last_frame, const cv::Mat &current_frame,
                     std::vector<cv::Mat> *concat_images);
};

}  // namespace assignment1
}  // namespace cv_project
#endif
