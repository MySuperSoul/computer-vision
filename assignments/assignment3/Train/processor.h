#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_TRAIN_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_TRAIN_PROCESSOR_H_

#include <iostream>
#include <map>

#include "computer-vision/assignments/assignment3/preprocessor/image_preprocessor.h"

namespace cv_project {
namespace assignment3 {

class Processor {
 public:
  explicit Processor() {
    image_preprocessor_.reset(new ImagePreprocessor());
    ReadTrainingImages();
  }

  explicit Processor(const std::string &dataset_path_prefix)
      : dataset_path_prefix_(dataset_path_prefix) {
    image_preprocessor_.reset(new ImagePreprocessor());
    ReadTrainingImages();
  }

 private:
  void ReadTrainingImages() {
    image_input_.open(dataset_path_prefix_, std::ios::out);
    if (!image_input_.is_open()) {
      std::cerr << "Can not open " << dataset_path_prefix_ << std::endl;
      return;
    }

    std::string s;
    while (std::getline(image_input_, s)) {
      auto values = cv_common::Util::SplitStrToVector(s);
      train_images_[values.front()] = values.back();
      if (train_images_.size() >= 10) {
        break;
      }
    }
    image_input_.close();
    std::cout << "Read in training images" << std::endl;
    FitFacesData();
  }

  void FitFacesData();

  std::string dataset_path_prefix_{
      "/roadstar/computer-vision/data/assignment3_data/lfw/train.txt"};
  std::ifstream image_input_;
  std::map<std::string, std::string> train_images_;
  std::unique_ptr<ImagePreprocessor> image_preprocessor_;
  cv::Mat faces_data_, roi_frame_;
};

}  // namespace assignment3
}  // namespace cv_project

#endif
