#include <iostream>

#include "computer-vision/assignments/assignment4/bird_view/view_processor.h"
#include "computer-vision/assignments/assignment4/camera_calibration/camera_calibrator.h"
#include "computer-vision/assignments/assignment4/hw4_argparser/HW4Argparser.h"

int main(int argc, char **argv) {
  cv_project::assignment4::HW4Argparser args;
  bool args_ok = args.parseArgs(argc, argv);

  if (args.help) {
    return 0;
  }

  if (!args_ok) {
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
