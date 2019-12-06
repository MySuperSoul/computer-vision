#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_TRAIN_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_TRAIN_PROCESSOR_H_

#include <iostream>
#include <map>

#include "computer-vision/assignments/assignment3/preprocessor/image_preprocessor.h"

namespace cv_project {
namespace assignment3 {

#define AINFO(x) std::cout << (x) << std::endl;

class Processor {
 public:
  explicit Processor(const std::string &model) : model_(model) {
    image_preprocessor_.reset(new ImagePreprocessor());
    file_storage_.open(model_, cv::FileStorage::WRITE);
    ReadTrainingImages();
  }

  explicit Processor(const std::string &model,
                     const std::string &dataset_path_prefix)
      : dataset_path_prefix_(dataset_path_prefix), model_(model) {
    image_preprocessor_.reset(new ImagePreprocessor());
    file_storage_.open(model_, cv::FileStorage::WRITE);
    ReadTrainingImages();
  }

  ~Processor() {
    cv::destroyAllWindows();
  }

  void Train();

  void ShowEigenFaces(const int &face_num);

 private:
  void ReadTrainingImages();

  void FitFacesData();

  void VectorToImage(cv::Mat *vec, cv::Mat *result_image, const int &width,
                     const int &height);

 private:
  std::string dataset_path_prefix_{
      "/roadstar/computer-vision/data/assignment3_data/lfw/train.txt"};
  std::string model_;
  std::ifstream image_input_;
  std::map<std::string, std::string> train_images_;
  std::unique_ptr<ImagePreprocessor> image_preprocessor_;
  cv::Mat faces_data_, roi_frame_, eigen_vector_, eigen_values_, eigen_faces_;
  cv::FileStorage file_storage_;
  int mask_width_{110}, mask_height_{135};
};

}  // namespace assignment3
}  // namespace cv_project

#endif
