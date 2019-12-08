#include <fstream>

#include "computer-vision/assignments/common/util.h"

int main(int argc, char **argv) {
  std::string prefix =
      "/roadstar/computer-vision/data/assignment3_data/att_faces/";

  std::system(
      "ls /roadstar/computer-vision/data/assignment3_data/att_faces/ > "
      "/roadstar/tmp.log");
  std::ifstream input("/roadstar/tmp.log");
  std::ofstream output_valid_path(
      "/roadstar/computer-vision/data/assignment3_data/att_faces/"
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

  std::system("rm /roadstar/tmp.log");

  output_valid_path.close();
  input.close();
  return 0;
}
