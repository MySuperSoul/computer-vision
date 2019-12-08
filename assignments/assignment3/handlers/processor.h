#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_HANDLERS_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_HANDLERS_PROCESSOR_H_

#include <iostream>
#include <map>

#include "computer-vision/assignments/assignment3/preprocessor/image_preprocessor.h"

namespace cv_project {
namespace assignment3 {

#define AINFO(x) std::cout << (x) << std::endl;
#define MAXDIS 200000000

class Processor {
 public:
  explicit Processor(const std::string &model) : model_(model) {
    AfterConstruct();
  }
  explicit Processor(const std::string &model, const double &energy)
      : model_(model), energy_(energy) {
    AfterConstruct();
  }

  explicit Processor(const std::string &model, const double &energy,
                     const std::string &training_set_path)
      : training_set_path_(training_set_path), model_(model), energy_(energy) {
    AfterConstruct();
  }

  ~Processor() {
    cv::destroyAllWindows();
  }

  void Train();

  void Test();

  void ShowEigenFaces(const int &face_num);

 private:
  inline void AfterConstruct() {
    image_preprocessor_.reset(new ImagePreprocessor());
    ReadImages();
  }

  void ReadImages();

  void FitFacesData();

  void VectorToImage(cv::Mat *vec, cv::Mat *result_image, const int &width,
                     const int &height);

  int GetEigenFacesNumFromEnergy();

 private:
  std::string training_set_path_{
      "/roadstar/computer-vision/data/assignment3_data/lfw/train.txt"};
  std::string testing_set_path_{
      "/roadstar/computer-vision/data/assignment3_data/lfw/test.txt"};
  std::string model_;
  std::ifstream image_input_;
  std::map<std::string, std::string> train_images_, testing_images_;
  std::map<int, std::pair<std::string, std::string>> train_map_;
  std::unique_ptr<ImagePreprocessor> image_preprocessor_;
  cv::Mat faces_data_, roi_frame_, eigen_vector_, eigen_values_, eigen_faces_;
  cv::FileStorage file_storage_, input_storage_;
  int mask_width_{110}, mask_height_{135}, image_count_{0};
  double energy_;
};

}  // namespace assignment3
}  // namespace cv_project

#endif
