#include <iostream>

#include "computer-vision/assignments/assignment3/Argparser/HW3Argparser.h"
#include "computer-vision/assignments/assignment3/handlers/processor.h"

int main(int argc, char **argv) {
  cv_project::assignment3::HW3Argparser args;
  bool args_ok = args.parseArgs(argc, argv);

  if (args.help) {
    return 0;
  }

  if (!args_ok) {
    std::cerr << "Invalid arguments occur" << std::endl;
    return -1;
  }

  std::unique_ptr<cv_project::assignment3::Processor> processor;
  processor.reset(new cv_project::assignment3::Processor(args.model));
  processor->Test();
  return 0;
}
