#ifndef CV_PROJECTS_ARGPARSER_H_
#define CV_PROJECTS_ARGPARSER_H_

#include <getopt.h>

#include <iostream>
#include <string>
#include <vector>

namespace cv_project {
namespace cv_common {

class Args {
 public:
  Args() {}
  ~Args() {}

 public:
  std::string data_dir;
  std::string save_dir;
  bool help{false};

 public:
  // function used to parse arguments from command lines
  inline bool parseArgs(int argc, char *argv[]) {
    while (1) {
      int arg;
      static struct option long_options[] = {
          {"help", no_argument, 0, 'h'},
          {"datadir", required_argument, 0, 'd'},
          {"savedir", required_argument, 0, 's'},
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
            save_dir = optarg;
          } else {
            std::cerr << "savedir requires argument to specify the output dir."
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

}  // namespace cv_common
}  // namespace cv_project

#endif
