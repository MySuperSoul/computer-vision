#include <fstream>

#include "computer-vision/assignments/common/util.h"

int main(int argc, char **argv) {
  std::string prefix =
      "/home/huangyifei/computer-vision/data/assignment3_data/att_faces/";

  std::system(
      "ls /home/huangyifei/computer-vision/data/assignment3_data/att_faces/ > "
      "/home/huangyifei/tmp.log");
  std::ifstream input("/home/huangyifei/tmp.log");
  std::ofstream output_valid_path(
      "/home/huangyifei/computer-vision/data/assignment3_data/att_faces/out/"
      "all-images.txt");

  std::string s;
  while (std::getline(input, s)) {
    auto paths =
        cv_project::cv_common::Util::GetAllImagePaths(prefix + s + "/");
    for (const auto &path : paths) {
      std::string path_str(path.c_str());
      output_valid_path << path_str + " " + s + "\n";
    }
    std::cout << "Done name: " << s << std::endl;
  }

  std::system("rm /home/huangyifei/tmp.log");

  output_valid_path.close();
  input.close();
  return 0;
}
