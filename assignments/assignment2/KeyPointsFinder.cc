#include "computer-vision/assignments/assignment2/KeyPointsFinder.h"

namespace cv_project {
namespace assignment2 {

namespace {
const int kLowerThreshold = 100;
const int kHigherThreshold = 200;
}  // namespace

void KeyPointsFinder::FindContours() {
  cv::Canny(gray_image_, edge_image_, kLowerThreshold, kHigherThreshold);
  cv::findContours(edge_image_, contours_, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
}

}  // namespace assignment2
}  // namespace cv_project
