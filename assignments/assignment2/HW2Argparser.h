#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT2_HW2_ARGPARSER_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT2_HW2_ARGPARSER_H_

#include "computer-vision/assignments/common/argparser.h"

namespace cv_project {
namespace assignment2 {

class HW2Argparser : public cv_common::Args {
 public:
  HW2Argparser() = default;
  ~HW2Argparser() = default;

 public:
  std::string input_image;

  bool parseArgs(int argc, char *argv[]) override {
    while (1) {
      int arg;
      static struct option long_options[] = {
          {"help", no_argument, 0, 'h'},
          {"input", required_argument, 0, 'i'},
          {nullptr, 0, nullptr, 0}};

      int option_index = 0;
      arg = getopt_long(argc, argv, "hd:iu", long_options, &option_index);

      if (arg == -1) break;

      switch (arg) {
        case 'h':
          help = true;
          return false;

        case 'i':
          if (optarg) {
            input_image = optarg;
          }
          break;

        default:
          return false;
      }
    }
    return true;
  }
};

}  // namespace assignment2
}  // namespace cv_project

#endif
