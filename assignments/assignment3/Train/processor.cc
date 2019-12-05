#include "computer-vision/assignments/assignment3/Train/processor.h"

namespace cv_project {
namespace assignment3 {

void Processor::FitFacesData() {
  for (const auto &image_label_pair : train_images_) {
    image_preprocessor_->SetImagePath(image_label_pair.first);
    image_preprocessor_->GerProcessedFaceRoi(&roi_frame_);
    if (faces_data_.empty()) {
      faces_data_ = roi_frame_.clone().reshape(0, 1);
    } else {
      faces_data_.push_back(roi_frame_.clone().reshape(0, 1));
    }
  }
}

}  // namespace assignment3
}  // namespace cv_project
