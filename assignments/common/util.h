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
      cv::glob(pattern, tmps, true);
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

  // function to replace the postfix
  // @param: return -> std::string
  static inline std::string ReplacePostFix(
      const std::string &input_name, const std::string &replaced_post_fix) {
    // input like apple.jpg
    auto dot_position = input_name.find_last_of('.');
    auto postfix_len = input_name.length() - dot_position - 1;
    return input_name.substr(0, input_name.length() - postfix_len) +
           replaced_post_fix;
  }

  // function to split str for "xx xx xxx xxx"
  static inline std::vector<std::string> SplitStrToVector(
      const std::string &input) {
    std::string s = input;
    std::vector<std::string> split_vec;

    while (s.find(" ") != -1) {
      auto blank_position = s.find_first_of(" ");
      split_vec.push_back(s.substr(0, blank_position));
      s = s.substr(blank_position + 1);
    }
    split_vec.push_back(s);
    return split_vec;
  }
};

}  // namespace cv_common
}  // namespace cv_project

#endif
