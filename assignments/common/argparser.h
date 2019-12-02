#ifndef COMPUTER_VISION_ASSIGNMENTS_COMMON_ARGPARSER_H_
#define COMPUTER_VISION_ASSIGNMENTS_COMMON_ARGPARSER_H_

#include <getopt.h>

#include <iostream>
#include <string>
#include <vector>

namespace cv_project {
namespace cv_common {

class Args {
 public:
  Args() = default;
  virtual ~Args() = default;

 public:
  bool help{false};

 public:
  // function used to parse arguments from command lines
  virtual bool parseArgs(int argc, char *argv[]) = 0;
};

}  // namespace cv_common
}  // namespace cv_project

#endif
