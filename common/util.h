#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace cv_project {
namespace cv_common {

void GetAllImagePaths(std::string image_path,
                      std::vector<std::string> &file_names) {
  std::vector<std::string> patterns = {"*.jpg", "*.jpeg", "*.png"};

}  // namespace cv_common
}  // namespace cv_common
