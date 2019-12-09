#include "computer-vision/assignments/assignment3/handlers/processor.h"

namespace cv_project {
namespace assignment3 {

void Processor::ReadImages() {
  image_input_.open(training_set_path_, std::ios::out);
  if (!image_input_.is_open()) {
    std::cerr << "Can not open " << training_set_path_ << std::endl;
    return;
  }

  std::string s;
  while (std::getline(image_input_, s)) {
    auto values = cv_common::Util::SplitStrToVector(s);
    train_images_[values.front()] = values.back();
  }
  image_input_.close();
  AINFO("Read in training images");

  image_input_.open(testing_set_path_, std::ios::out);
  while (std::getline(image_input_, s)) {
    auto values = cv_common::Util::SplitStrToVector(s);
    testing_images_[values.front()] = values.back();
  }
  image_input_.close();
  AINFO("Read in testing images");
  FitFacesData();
}

void Processor::FitFacesData() {
  for (const auto &image_label_pair : train_images_) {
    image_preprocessor_->SetImagePath(image_label_pair.first);
    image_preprocessor_->GetProcessedFaceRoi(&roi_frame_);
    train_map_[image_count_++] =
        std::make_pair(image_label_pair.first, image_label_pair.second);
    if (faces_data_.empty()) {
      faces_data_ = roi_frame_.clone().reshape(1, 1);
    } else if (roi_frame_.rows * roi_frame_.cols == faces_data_.cols) {
      faces_data_.push_back(roi_frame_.clone().reshape(1, 1));
    } else {
      continue;
    }
  }
}

int Processor::GetEigenFacesNumFromEnergy() {
  int tmp_num = 0;
  double tmp_sum = 0;
  for (int i = 0; i < eigen_values_.rows; i++) {
    tmp_sum += eigen_values_.at<double>(i, 0);
    if (tmp_sum >= energy_) {
      tmp_num = i + 1;
      break;
    }
  }
  return tmp_num;
}

double CalculateDistance(const cv::Mat &image) {
  double dis = 0.0;
  for (int i = 0; i < image.cols; i++) {
    dis += std::pow(image.at<double>(0, i), 2);
  }
  dis = std::sqrt(dis);
  dis /= image.cols;
  return dis;
}

void Processor::Test() {
  input_storage_.open(model_, cv::FileStorage::READ);
  input_storage_["eigen_vector"] >> eigen_vector_;
  input_storage_["mean_face"] >> mean_face_;

  cv::Mat images_data, test_data;
  faces_data_.convertTo(images_data, CV_64F);
  images_data = images_data * eigen_vector_;

  for (auto iter = testing_images_.begin(); iter != testing_images_.end();
       iter++) {
    image_preprocessor_->SetImagePath(iter->first);
    image_preprocessor_->GetProcessedFaceRoi(&test_data);
    test_data = test_data.reshape(1, 1);
    test_data.convertTo(test_data, CV_64F);
    test_data = test_data * eigen_vector_;

    double min_distance = CalculateDistance(images_data.row(0) - test_data);
    int min_index = 0;
    for (int i = 1; i < images_data.rows; i++) {
      double distance = CalculateDistance(images_data.row(i) - test_data);
      if (distance < min_distance) {
        min_distance = distance;
        min_index = i;
      }
    }

    // output image and labels
    cv::Mat test_image, predict_image;
    test_image = cv::imread(std::string(iter->first));
    predict_image = cv::imread(std::string(train_map_[min_index].first));

    cv::putText(predict_image, "Predict: " + train_map_[min_index].second,
                {0, 20}, cv::FONT_HERSHEY_PLAIN, 0.7, {0, 0, 255});
    cv::putText(predict_image, "Label: " + iter->second, {0, 40},
                cv::FONT_HERSHEY_PLAIN, 0.7, {0, 255, 0});
    cv::resize(test_image, test_image,
               {static_cast<int>(test_image.cols * 2),
                static_cast<int>(test_image.rows * 2)});
    cv::resize(predict_image, predict_image,
               {static_cast<int>(predict_image.cols * 2),
                static_cast<int>(predict_image.rows * 2)});

    cv::imshow("Test-Image", test_image);
    cv::imshow("Predict-Image", predict_image);

    cv::waitKey(0);
  }
  input_storage_.release();
}

void Processor::Train() {
  file_storage_.open(model_, cv::FileStorage::WRITE);
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
  cv::eigen(cov_mat, eigen_values_, eigen_vector_);
  AINFO("End calculating eigen vectors");

  eigen_vector_ = (images_data.t() * eigen_vector_.t());
  cv::normalize(eigen_values_, eigen_values_, 1.0, 0.0, cv::NORM_L1);

  int num = GetEigenFacesNumFromEnergy();
  AINFO("Select Top " + std::to_string(num) + " Eigen faces");

  eigen_vector_ = eigen_vector_.colRange(0, num);
  file_storage_ << "eigen_vector" << eigen_vector_;
  file_storage_ << "mean_face" << mean_mat;
  file_storage_.release();
  AINFO("Engine saved in " + model_);
}

void Processor::VectorToImage(cv::Mat *vec, cv::Mat *result_image,
                              const int &width, const int &height,
                              bool with_normalize) {
  int data_type = (*vec).type();
  cv::Mat result(cv::Size(width, height), data_type);
  for (int i = 0; i < height; i++) {
    (*vec)
        .colRange(i * width, (i + 1) * width)
        .convertTo(result.row(i), data_type);
  }
  if (with_normalize) {
    cv::normalize(result, result, 1.0, 0.0, cv::NORM_MINMAX);
  } else {
    cv::normalize(result, result, 255.0, 0.0, cv::NORM_MINMAX);
  }
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
