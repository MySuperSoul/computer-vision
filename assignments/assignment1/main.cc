#include <iostream>

#include "computer-vision/assignments/common/argparser.h"
#include "computer-vision/assignments/common/util.h"

void PrintHelpInfo() {
  std::cout << "Usage: ./bazel-bin/assignment1/assignment1 [-h or "
               "--help] [-d or --datadir=<path to data directory>] [-s or "
               "--savedir=<path to store the output>] [-v or "
               "--vedioname=<filename of input vedio file>]"
            << std::endl;
  std::cout << "--help      Display help information" << std::endl;
  std::cout << "--datadir   Specify data directory, required argument here"
            << std::endl;
  std::cout
      << "--savedir   Specify output directory to store, required argument here"
      << std::endl;
  std::cout << "--vedioname    Specify input vedio filename" << std::endl;
}

int main(int argc, char **argv) {
  cv_project::cv_common::Args args;
  bool args_ok = args.parseArgs(argc, argv);

  if (args.help) {
    PrintHelpInfo();
    return 0;
  }

  if (!args_ok) {
    std::cerr << "Invalid arguments occur" << std::endl;
    PrintHelpInfo();
    return -1;
  }

  cv::Mat a = cv::imread("/roadstar/computer-vision/data/1.png");
  cv::imshow("test", a);
  cv::waitKey(0);

  return 0;
}