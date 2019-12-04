#include <fstream>

#include "computer-vision/assignments/assignment3/EyePositionCalibrator/EyePositionCalibrator.h"
#include "computer-vision/assignments/common/util.h"

int main(int argc, char **argv) {
  cv_project::assignment3::EyePositionCalibrator calibrator;

  std::string prefix =
      "/roadstar/computer-vision/data/assignment3_data/lfw/lfw/";

  std::system(
      "ls /roadstar/computer-vision/data/assignment3_data/lfw/lfw/ > "
      "/roadstar/tmp.log");
  std::ifstream input("/roadstar/tmp.log");
  std::ofstream output_eye_center;
  std::ofstream output_valid_path(
      "/roadstar/computer-vision/data/assignment3_data/lfw/all-images.txt");

  std::string s;
  while (std::getline(input, s)) {
    auto paths =
        cv_project::cv_common::Util::GetAllImagePaths(prefix + s + "/");
    for (const auto &path : paths) {
      calibrator.SetImage(path, s);
      if (calibrator.DoCalibration()) {
        std::string path_str(path.c_str());
        std::string eye_path_str =
            cv_project::cv_common::Util::ReplacePostFix(path_str, "txt");
        output_eye_center.open(eye_path_str, std::ios::out);
        output_eye_center << calibrator.GetEyeCenter();
        output_eye_center.close();
        output_valid_path << path_str + " " + s + "\n";
      }
    }
    std::cout << "Done name: " << s << std::endl;
  }

  std::system("rm /roadstar/tmp.log");

  output_valid_path.close();
  input.close();
  return 0;
}
