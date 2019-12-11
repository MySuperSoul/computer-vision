#include <iostream>

#include "computer-vision/assignments/assignment4/bird_view/view_processor.h"
#include "computer-vision/assignments/assignment4/camera_calibration/camera_calibrator.h"
#include "computer-vision/assignments/assignment4/hw4_argparser/HW4Argparser.h"

void PrintHelpInfo() {
  std::cout
      << "Usage: "
         "./bazel-bin/computer-vision/assignments/assignment4/assignment4 "
         "[--width board_width] [--height board_height] [--num_boards max "
         "selected board images] [--scale image scale] [--data_prefix path "
         "prefix of the calibration data] [--xml_path path to store the xml "
         "output] [--image_path path of bird_view image]"
      << std::endl;
  std::cout << "Example: "
               "./bazel-bin/computer-vision/assignments/assignment4/"
               "assignment4 \n --width=12 \n --height=12 \n --num_boards=20 "
               "\n --scale=1.0 \n "
               "--data_prefix=/home/huangyifei/data/ \n "
               "--image_path=/home/huangyifei/data/birdseye/IMG_0220L.jpg"
            << std::endl;
}

int main(int argc, char **argv) {
  cv_project::assignment4::HW4Argparser args;
  bool args_ok = args.parseArgs(argc, argv);

  if (args.help) {
    PrintHelpInfo();
    return 0;
  }

  if (!args_ok) {
    PrintHelpInfo();
    std::cerr << "Invalid arguments occur" << std::endl;
    return -1;
  }

  std::unique_ptr<cv_project::assignment4::CameraCalibrator> calibrator;
  calibrator.reset(new cv_project::assignment4::CameraCalibrator(
      args.board_width, args.board_height, args.num_boards, args.image_scale,
      args.data_prefix, args.xml_path));
  calibrator->DoCalibration();

  // optimal: show undistort images
  // calibrator->ShowUndistortImages();

  std::unique_ptr<cv_project::assignment4::BirdViewProcessor>
      bird_view_processor;
  bird_view_processor.reset(new cv_project::assignment4::BirdViewProcessor(
      args.image_path, args.xml_path));
  bird_view_processor->DoBirdViewTransform(true);
  return 0;
}
