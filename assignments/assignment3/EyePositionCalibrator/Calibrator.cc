#include <fstream>

#include "computer-vision/assignments/assignment3/EyePositionCalibrator/EyePositionCalibrator.h"
#include "computer-vision/assignments/common/util.h"

int main(int argc, char **argv) {
  cv_project::assignment3::EyePositionCalibrator calibrator;

  std::string prefix =
      "/home/huangyifei/computer-vision/data/assignment3_data/att_faces/";

  std::system(
      "ls /home/huangyifei/computer-vision/data/assignment3_data/att_faces/ > "
      "/home/huangyifei/tmp.log");
  std::ifstream input("/home/huangyifei/tmp.log");
  std::ofstream output_eye_center;

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
      }
    }
    std::cout << "Done name: " << s << std::endl;
  }

  std::system("rm /home/huangyifei/tmp.log");

  input.close();
  return 0;
}
