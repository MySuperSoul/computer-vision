#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_HANDLERS_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_HANDLERS_PROCESSOR_H_

#include <iostream>
#include <map>

#include "computer-vision/assignments/assignment3/preprocessor/image_preprocessor.h"

namespace cv_project {
namespace assignment3 {

#define AINFO(x) std::cout << (x) << std::endl;

class Processor {
 public:
  explicit Processor(const std::string &model,
                     const std::string &out_path_prefix)
      : out_path_prefix_(out_path_prefix), model_(model) {
    AfterConstruct();
  }

  explicit Processor(const std::string &model,
                     const std::string &out_path_prefix, const double &energy)
      : out_path_prefix_(out_path_prefix), model_(model), energy_(energy) {
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
    training_set_path_ = out_path_prefix_ + "train.txt";
    testing_set_path_ = out_path_prefix_ + "test.txt";
    image_preprocessor_.reset(
        new ImagePreprocessor());
    ReadImages();
  }

  void ReadImages();

  void FitFacesData();

  void VectorToImage(cv::Mat *vec, cv::Mat *result_image, const int &width,
                     const int &height, bool with_normalize = true);

  int GetEigenFacesNumFromEnergy();

 private:
  std::string training_set_path_, testing_set_path_, out_path_prefix_;
  std::string model_;
  std::ifstream image_input_;
  std::map<std::string, std::string> train_images_, testing_images_;
  std::map<int, std::pair<std::string, std::string>> train_map_;
  std::unique_ptr<ImagePreprocessor> image_preprocessor_;
  cv::Mat faces_data_, roi_frame_, eigen_vector_, eigen_values_, eigen_faces_,
      mean_face_;
  cv::FileStorage file_storage_, input_storage_;
  int mask_width_{92}, mask_height_{112}, image_count_{0};
  double energy_;
};

}  // namespace assignment3
}  // namespace cv_project

#endif
