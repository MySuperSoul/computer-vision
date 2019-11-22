#ifndef COMPUTER_VISION_ASSIGNMENTS_COMMON_UTIL_H_
#define COMPUTER_VISION_ASSIGNMENTS_COMMON_UTIL_H_

#include <cstdlib>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace cv_project {
namespace cv_common {

class Util {
 public:
  Util() = default;
  ~Util() = default;
  // function to get all the image paths under sprcified directory
  // @param: return-> vector<String>
  static inline std::vector<cv::String> GetAllImagePaths(
      cv::String image_path) {
    std::vector<cv::String> patterns = {"*.jpg", "*.jpeg", "*.png"};
    std::vector<cv::String> paths, tmps;

    for (auto v : patterns) {
      cv::String pattern = image_path + v;
      cv::glob(pattern, tmps);
      paths.insert(paths.end(), tmps.begin(), tmps.end());
      tmps.clear();
    }
    return paths;
  }

  // function to judge whether to add `/` in the final full path
  static inline std::string GetValidFullPath(std::string path) {
    if (path.back() == '/') {
      return path;
    } else {
      return path + '/';
    }
  }

  static inline int GetRandNum(const int &left_bound, const int &right_bound) {
    // requires that left_bound is lower than right_bound
    return (rand() % (right_bound - left_bound + 1)) + left_bound;
  }
};

}  // namespace cv_common
}  // namespace cv_project

#endif
