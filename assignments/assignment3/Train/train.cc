#include "computer-vision/assignments/assignment3/Train/processor.h"

int main(int argc, char **argv) {
  std::unique_ptr<cv_project::assignment3::Processor> processor;
  processor.reset(new cv_project::assignment3::Processor(
      "/roadstar/computer-vision/data/assignment3_data/lfw/face.engine"));
  processor->Train();
  processor->ShowEigenFaces(10);
  return 0;
}
