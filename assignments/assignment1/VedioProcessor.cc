#include "computer-vision/assignments/assignment1/VedioProcessor.h"

namespace cv_project {
namespace assignment1 {

// constructor
VedioProcessor::VedioProcessor(const std::string &video_path,
                               const std::string &window_name) {
  video_path_ = video_path;
  window_name_ = window_name;
  video_capture_.open(cv::String(video_path_));

  if (!video_capture_.isOpened()) {
    std::cerr << "Failed to open video: " << video_path_
              << ". Check if the path is right." << std::endl;
    return;
  }

  cv::namedWindow(window_name_, cv::WINDOW_AUTOSIZE);
}

// function to play the vedio specified by vedio path
void VedioProcessor::Play(bool with_subtitles) {
  frame_rate_ = video_capture_.get(cv::CAP_PROP_FPS);
  frame_count_ = video_capture_.get(cv::CAP_PROP_FRAME_COUNT);

  double delay_time = 1000.0 / frame_rate_;
  double control_rate = 0.1;

  while (control_rate < frame_count_) {
    video_capture_.read(image_);
    cv::imshow(window_name_, image_);
    std::cout << window_name_ << std::endl;
    cv::waitKey(static_cast<int>(delay_time));
    control_rate++;
  }
}

}  // namespace assignment1
}  // namespace cv_project
