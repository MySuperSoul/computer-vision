#include "computer-vision/assignments/assignment3/Train/processor.h"

namespace cv_project {
namespace assignment3 {

void Processor::ReadTrainingImages() {
  image_input_.open(dataset_path_prefix_, std::ios::out);
  if (!image_input_.is_open()) {
    std::cerr << "Can not open " << dataset_path_prefix_ << std::endl;
    return;
  }

  std::string s;
  while (std::getline(image_input_, s)) {
    auto values = cv_common::Util::SplitStrToVector(s);
    train_images_[values.front()] = values.back();
    if (train_images_.size() >= 200) {
      break;
    }
  }
  image_input_.close();
  AINFO("Read in training images");
  FitFacesData();
}

void Processor::FitFacesData() {
  for (const auto &image_label_pair : train_images_) {
    image_preprocessor_->SetImagePath(image_label_pair.first);
    image_preprocessor_->GetProcessedFaceRoi(&roi_frame_);
    if (faces_data_.empty()) {
      faces_data_ = roi_frame_.clone().reshape(1, 1);
    } else if (roi_frame_.rows * roi_frame_.cols == faces_data_.cols) {
      faces_data_.push_back(roi_frame_.clone().reshape(1, 1));
    } else {
      continue;
    }
  }
}

void Processor::Train() {
  cv::Mat cov_mat, mean_mat;

  cv::Mat images_data;
  faces_data_.convertTo(images_data, CV_64FC1);

  AINFO("Begin calculating cov matrix");
  cv::calcCovarMatrix(images_data, cov_mat, mean_mat, CV_COVAR_ROWS);
  AINFO("Done calculating cov matrix");

  for (int i = 0; i < images_data.rows; i++) {
    images_data.row(i) -= mean_mat;
  }

  AINFO("Begin calculating eigen vectors");
  cv::eigenNonSymmetric(cov_mat, eigen_values_, eigen_vector_);
  AINFO("End calculating eigen vectors");

  eigen_vector_ = (images_data.t() * eigen_vector_.t());
  file_storage_ << "eigen_vector" << eigen_vector_;
  file_storage_.release();
  AINFO("Engine saved in " + model_);
}

void Processor::VectorToImage(cv::Mat *vec, cv::Mat *result_image,
                              const int &width, const int &height) {
  int data_type = (*vec).type();
  cv::Mat result(cv::Size(width, height), data_type);
  for (int i = 0; i < height; i++) {
    (*vec)
        .colRange(i * width, (i + 1) * width)
        .convertTo(result.row(i), data_type);
  }

  cv::normalize(result, result, 1.0, 0.0, cv::NORM_MINMAX);
  (*result_image) = result;
}

void Processor::ShowEigenFaces(const int &face_num) {
  std::vector<cv::Mat> faces_vec;
  cv::Mat face_image;
  for (int i = 0; i < std::min(face_num, eigen_vector_.cols); i++) {
    cv::Mat col_img = eigen_vector_.col(i).t();
    VectorToImage(&col_img, &face_image, mask_width_, mask_height_);
    faces_vec.push_back(face_image.clone());
  }

  cv::hconcat(faces_vec, eigen_faces_);
  cv::imshow("Top10Eigenfaces", eigen_faces_);
  cv::waitKey(0);
}

}  // namespace assignment3
}  // namespace cv_project
