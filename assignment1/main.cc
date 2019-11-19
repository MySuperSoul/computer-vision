#include <iostream>

#include "projects/common/argparser.h"

void printHelpInfo() {
  std::cout << "Usage: ./bazel-bin/assignment1/assignment1 [-h or "
               "--help] [-d or --datadir=<path to data directory>] [-s or "
               "--savedir=<path to store the output>]"
            << std::endl;
  std::cout << "--help      Display help information" << std::endl;
  std::cout << "--datadir   Specify data directory, required argument here"
            << std::endl;
  std::cout
      << "--savedir   Specify output directory to store, required argument here"
      << std::endl;
}

int main(int argc, char **argv) {
  cv_project::cv_common::Args args;
  bool argsOK = args.parseArgs(argc, argv);

  if (args.help) {
    printHelpInfo();
    return 0;
  }

  if (!argsOK) {
    std::cerr << "Invalid arguments occur" << std::endl;
    printHelpInfo();
    return -1;
  }

  std::cout << args.data_dir << " " << args.save_dir << std::endl;
  return 0;
}
