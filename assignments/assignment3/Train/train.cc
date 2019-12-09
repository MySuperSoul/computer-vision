#include "computer-vision/assignments/assignment3/Argparser/HW3Argparser.h"
#include "computer-vision/assignments/assignment3/handlers/processor.h"

namespace {
const int kFaceNum = 10;
}  // namespace

void PrintHelpInfo() {
  std::cout << "Usage: "
               "./bazel-bin/computer-vision/assignments/assignment3/Train"
               "train [-h or "
               "--help] [-i or --input=<path to train txt>] [-m or "
               "--model=<path to store the training model>] [-M or "
               "--mask=<mask path provided>] [-e or --energy=<energy input>]"
            << std::endl;
  std::cout << "--help      Display help information" << std::endl;
  std::cout
      << "--input   Specify train txt for training, required argument here"
      << std::endl;
  std::cout << "--model Specify the path for saving training model"
            << std::endl;
  std::cout << "--mask Specify the mask file to crop the face area"
            << std::endl;
  std::cout << "--energy The energy to choose the num of eigen faces"
            << std::endl;
  std::cout
      << "example: "
         "./bazel-bin/computer-vision/assignments/assignment3/Train/train "
         "--input=/home/huangyifei/data/att_faces/ "
         "--model=/home/huangyifei/data/face.engine "
         "--mask=/home/huangyifei/data/mask.txt --energy=0.9 "
      << std::endl;
}

int main(int argc, char **argv) {
  cv_project::assignment3::HW3Argparser args;
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

  std::unique_ptr<cv_project::assignment3::Processor> processor;
  processor.reset(new cv_project::assignment3::Processor(
      args.model, args.input_prefix, args.energy));
  processor->Train();
  processor->ShowEigenFaces(kFaceNum);
  return 0;
}
