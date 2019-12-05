#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "computer-vision/assignments/common/util.h"

namespace {
const std::string kPrefix =
    "/roadstar/computer-vision/data/assignment3_data/lfw/";
const int kThreshold = 4;
std::map<std::string, std::vector<std::string>> kAll;
}  // namespace

void FitAllMap(std::ifstream *input) {
  std::string s;
  while (std::getline(*input, s)) {
    auto v = cv_project::cv_common::Util::SplitStrToVector(s);
    kAll[v.back()].push_back(v.front());
  }
}

void SplitDataset() {
  std::ofstream output_train, output_test;
  output_train.open(kPrefix + "train.txt", std::ios::out);
  output_test.open(kPrefix + "test.txt", std::ios::out);

  for (auto iter = kAll.begin(); iter != kAll.end(); iter++) {
    if (iter->second.size() >= kThreshold) {
      // get the last sample to be test image
      std::string s = iter->second.back();
      output_test << s + " " + iter->first + "\n";
      iter->second.pop_back();
    }
  }

  // write kAll to train.txt
  for (const auto &item : kAll) {
    for (const auto &image : item.second) {
      output_train << image + " " + item.first + "\n";
    }
    std::cout << "Done Train name: " << item.first << std::endl;
  }

  output_test.close();
  output_train.close();
}

int main(int argc, char **argv) {
  std::ifstream input;
  input.open(kPrefix + "all-images.txt");

  if (!input.is_open()) {
    std::cerr << "Error open all-images.txt" << std::endl;
    return -1;
  }

  FitAllMap(&input);
  input.close();
  SplitDataset();

  return 0;
}
