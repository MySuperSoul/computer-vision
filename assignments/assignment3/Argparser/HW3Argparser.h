#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_HW3_ARGPARSER_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT3_HW3_ARGPARSER_H_

#include "computer-vision/assignments/common/argparser.h"

namespace cv_project {
namespace assignment3 {

class HW3Argparser : public cv_common::Args {
 public:
  HW3Argparser() = default;
  ~HW3Argparser() = default;

 public:
  std::string input_image;
  std::string model;
  double energy;

  bool parseArgs(int argc, char *argv[]) override {
    while (1) {
      int arg;
      static struct option long_options[] = {
          {"help", no_argument, 0, 'h'},
          {"input", required_argument, 0, 'i'},
          {"model", required_argument, 0, 'm'},
          {"energy", required_argument, 0, 'e'},
          {nullptr, 0, nullptr, 0}};

      int option_index = 0;
      arg = getopt_long(argc, argv, "hd:iu", long_options, &option_index);

      if (arg == -1) break;

      switch (arg) {
        case 'h':
          help = true;
          return false;

        case 'i':
          input_image = optarg;
          break;

        case 'm':
          model = optarg;
          break;

        case 'e':
          energy = std::stod(optarg);
          break;

        default:
          return false;
      }
    }
    return true;
  }
};

}  // namespace assignment3
}  // namespace cv_project
#endif