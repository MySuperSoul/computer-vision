#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_PREPROCESSOR_IMAGE_PREPROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_PREPROCESSOR_IMAGE_PREPROCESSOR_H_

#include "computer-vision/assignments/assignment3/preprocessor/roi_creater.h"

namespace cv_project {
namespace assignment3 {

class ImagePreprocessor {
 public:
  explicit ImagePreprocessor() {
    roi_creater_.reset(new RoiCreater());
  }

  ~ImagePreprocessor() = default;

  void SetImagePath(const std::string &image_path);
  void GetProcessedFaceRoi(cv::Mat *face_roi);

 private:
  cv::Mat roi_frame_;
  cv::Mat roi_processed_frame_;
  std::unique_ptr<RoiCreater> roi_creater_;
};

}  // namespace assignment3
}  // namespace cv_project
#endif
