#include "computer-vision/assignments/assignment3/preprocessor/image_preprocessor.h"

namespace cv_project {
namespace assignment3 {

void ImagePreprocessor::SetImagePath(const std::string &image_path) {
  roi_creater_->SetImagePath(image_path);
  roi_frame_ = roi_creater_->GetFaceRoiFrame();
}

void ImagePreprocessor::GerProcessedFaceRoi(cv::Mat *face_roi) {
  cv::cvtColor(roi_frame_, roi_processed_frame_, CV_BGR2GRAY);
  cv::equalizeHist(roi_processed_frame_, roi_processed_frame_);
  *face_roi = roi_processed_frame_;
}

}  // namespace assignment3
}  // namespace cv_project
