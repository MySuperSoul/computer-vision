#ifndef COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT4_HW4_ARGPARSER_H_
#define COMPUTER_VISION_ASSIGNMENTS_ASSIGNMENT4_HW4_ARGPARSER_H_

#include "computer-vision/assignments/common/argparser.h"

namespace cv_project {
namespace assignment4 {

class HW4Argparser : public cv_common::Args {
 public:
  HW4Argparser() = default;
  ~HW4Argparser() = default;

 public:
  int board_width, board_height, num_boards;
  double image_scale;
  std::string data_prefix, xml_path, image_path;

  bool parseArgs(int argc, char *argv[]) override {
    while (1) {
      int arg;
      static struct option long_options[] = {
          {"help", no_argument, 0, 'h'},
          {"width", required_argument, 0, 'w'},
          {"height", required_argument, 0, 'H'},
          {"num_boards", required_argument, 0, 'n'},
          {"scale", required_argument, 0, 's'},
          {"data_prefix", required_argument, 0, 'd'},
          {"xml_path", required_argument, 0, 'x'},
          {"image_path", required_argument, 0, 'i'},
          {nullptr, 0, nullptr, 0}};

      int option_index = 0;
      arg = getopt_long(argc, argv, "hd:iu", long_options, &option_index);

      if (arg == -1) break;

      switch (arg) {
        case 'h':
          help = true;
          return false;

        case 'w':
          board_width = std::stoi(optarg);
          break;

        case 'H':
          board_height = std::stoi(optarg);
          break;

        case 'n':
          num_boards = std::stoi(optarg);
          break;

        case 's':
          image_scale = std::stod(optarg);
          break;

        case 'd':
          data_prefix = optarg;
          break;

        case 'x':
          xml_path = optarg;
          break;

        case 'i':
          image_path = optarg;
          break;

        default:
          return false;
      }
    }
    return true;
  }
};

}  // namespace assignment4
}  // namespace cv_project
#endif
