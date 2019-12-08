#include <fstream>
#include <opencv2/opencv.hpp>

#include "computer-vision/assignments/assignment3/preprocessor/image_preprocessor.h"
#include "computer-vision/assignments/common/util.h"

namespace {
const std::string kPrefix =
    "/home/huangyifei/computer-vision/data/assignment3_data/att_faces/";
}

int main(int argc, char **argv) {
  std::ifstream input, eye_input;
  input.open(kPrefix + "train.txt");

  std::string s, eye;
  std::unique_ptr<cv_project::assignment3::ImagePreprocessor>
      image_preprocessor;
  image_preprocessor.reset(new cv_project::assignment3::ImagePreprocessor());

  while (std::getline(input, s)) {
    std::string image_path = s.substr(0, s.find_first_of(" "));
    image_preprocessor->SetImagePath(image_path);
    cv::Mat a;
    image_preprocessor->GetProcessedFaceRoi(&a);
    // std::string eye_path =
    //    cv_project::cv_common::Util::ReplacePostFix(image_path, "txt");
    // eye_input.open(eye_path);
    // std::getline(eye_input, eye);
    // eye_input.close();

    // auto eye_centers = cv_project::cv_common::Util::SplitStrToVector(eye);
    // int x1 = std::stoi(eye_centers[0]);
    // int y1 = std::stoi(eye_centers[1]);
    // int x2 = std::stoi(eye_centers[2]);
    // int y2 = std::stoi(eye_centers[3]);

    // cv::Mat a = cv::imread(image_path);
    // cv::circle(a, {x1, y1}, 5, cv::Scalar(0, 0, 255));
    // cv::circle(a, {x2, y2}, 5, cv::Scalar(0, 255, 0));
    // int x = std::min(x1, x2);
    // int y = std::min(y1, y2);
    // int xdiff = 40;
    // int ydiff = 55;
    // int width = 110, height = 135;
    // cv::rectangle(a, {x - xdiff, y - ydiff},
    //              {x - xdiff + width, y - ydiff + height},
    //              cv::Scalar(255, 0, 0));
    cv::imshow("Test", a);
    cv::waitKey(0);
  }

  cv::destroyAllWindows();
  input.close();
  return 0;
}
