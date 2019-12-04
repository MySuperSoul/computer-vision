#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT1_HW1_ARGPARSER_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT1_HW1_ARGPARSER_H_

#include "computer-vision/assignments/common/argparser.h"

namespace cv_project {
namespace assignment1 {

class HW1Argparser : public cv_common::Args {
 public:
  HW1Argparser() = default;
  ~HW1Argparser() = default;

 public:
  std::string data_dir;
  std::string save_path;
  std::string videoname;

  bool parseArgs(int argc, char *argv[]) override {
    while (1) {
      int arg;
      static struct option long_options[] = {
          {"help", no_argument, 0, 'h'},
          {"datadir", required_argument, 0, 'd'},
          {"savepath", required_argument, 0, 's'},
          {"videoname", required_argument, 0, 'v'},
          {nullptr, 0, nullptr, 0}};

      int option_index = 0;
      arg = getopt_long(argc, argv, "hd:iu", long_options, &option_index);

      if (arg == -1) break;

      switch (arg) {
        case 'h':
          help = true;
          return false;
        case 'd':
          if (optarg) {
            data_dir = optarg;
          } else {
            std::cerr << "datadir requires argument in." << std::endl;
            return false;
          }
          break;
        case 's':
          if (optarg) {
            save_path = optarg;
          } else {
            std::cerr << "savepath requires argument to specify the output dir."
                      << std::endl;
            return false;
          }
          break;
        case 'v':
          if (optarg) {
            videoname = optarg;
          } else {
            std::cerr
                << "videoname requires argument to match the input vedio file"
                << std::endl;
            return false;
          }
          break;

        default:
          return false;
      }
    }
    return true;
  }
};

}  // namespace assignment1
}  // namespace cv_project

#endif
