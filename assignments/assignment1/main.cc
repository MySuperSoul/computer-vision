#include <unistd.h>

#include <iostream>

#include "computer-vision/assignments/assignment1/VideoProcessor.h"
#include "computer-vision/assignments/common/argparser.h"
#include "computer-vision/assignments/common/util.h"

void PrintHelpInfo() {
  std::cout << "Usage: "
               "./bazel-bin/computer-vision/assignments/assignment1/"
               "assignment1 [-h or "
               "--help] [-d or --datadir=<path to data directory>] [-s or "
               "--savepath=<path to store the output>] [-v or "
               "--videoname=<filename of input video file>]"
            << std::endl;
  std::cout << "--help      Display help information" << std::endl;
  std::cout << "--datadir   Specify data directory, required argument here"
            << std::endl;
  std::cout << "--savepath   Specify output directory to store, required "
               "argument here"
            << std::endl;
  std::cout << "--videoname    Specify input video filename" << std::endl;
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

  std::string video_full_path =
      cv_project::cv_common::Util::GetValidFullPath(args.data_dir) +
      args.videoname;

  std::unique_ptr<cv_project::assignment1::VideoProcessor> processor;
  processor.reset(new cv_project::assignment1::VideoProcessor(video_full_path,
                                                              args.save_path));
  processor->Process(cv_project::cv_common::Util::GetAllImagePaths(
      cv_project::cv_common::Util::GetValidFullPath(args.data_dir)));

  processor.reset(new cv_project::assignment1::VideoProcessor(args.save_path,
                                                              args.save_path));
  processor->Play(true);
  return 0;
}
