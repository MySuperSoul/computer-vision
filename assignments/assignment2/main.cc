#include <iostream>
#include <string>

#include "computer-vision/assignments/assignment2/HW2Argparser.h"
#include "computer-vision/assignments/assignment2/KeyPointsFinder.h"
#include "computer-vision/assignments/common/renderer.h"

namespace {
const int kMinCountNum = 5;
const int kThickness = 1;
const int kLineType = CV_AA;
const cv::Scalar kColor = cv::Scalar(0, 0, 255);
const std::string kWindow = "assignment2";
const std::string kOrigin = "Origin-Image";
std::unique_ptr<cv_project::cv_common::Renderer> kRenderer;
std::unique_ptr<cv_project::assignment2::KeyPointsFinder> kFinder = nullptr;

}  // namespace

void PrintHelpInfo() {
  std::cout << "Usage: "
               "./bazel-bin/computer-vision/assignments/assignment2/"
               "assignment2 [-h or "
               "--help] [-i or --input=<path to input image full path>]"
            << std::endl;
  std::cout << "--help      Display help information" << std::endl;
  std::cout << "--input   Specify input image full path, required argument here"
            << std::endl;
  std::cout
      << "example: "
         "./bazel-bin/computer-vision/assignments/assignment2/assignment2 "
         "--input=/home/huangyifei/data/input.jpg "
      << std::endl;
}

void FitEclipse(const std::vector<std::vector<cv::Point>> &contours,
                cv::Mat *image) {
  for (auto contour : contours) {
    if (contour.size() < kMinCountNum) {
      continue;
    }

    cv::RotatedRect box = cv::fitEllipse(contour);
    kRenderer->DrawEclipse(image, box, kColor, kThickness, kLineType);
  }
}

void ProcessImage(cv::Mat *image) {
  kFinder.reset(new cv_project::assignment2::KeyPointsFinder(*image));

  auto contours = kFinder->GetContours();
  FitEclipse(contours, image);
}

int main(int argc, char **argv) {
  cv_project::assignment2::HW2Argparser args;
  bool args_ok = args.parseArgs(argc, argv);

  if (args.help) {
    PrintHelpInfo();
    return 0;
  }

  if (!args_ok) {
    std::cerr << "Invalid arguments occur" << std::endl;
    PrintHelpInfo();
    return -1;
  }

  cv::Mat image = cv::imread(args.input_image);
  if (image.empty()) {
    std::cerr << "Check if the image path is correct" << std::endl;
  }

  kRenderer->ShowImage(image, kOrigin);
  ProcessImage(&image);
  kRenderer->ShowImage(image, kWindow);
  cv::waitKey(0);
  cv::destroyAllWindows();
  return 0;
}
