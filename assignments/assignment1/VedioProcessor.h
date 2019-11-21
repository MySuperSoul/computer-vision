#ifndef COMPUTER_VISION_ASSIGNMENTS_VEDIO_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_VEDIO_PROCESSOR_H_

#include <opencv2/opencv.hpp>
#include <vector>

namespace cv_project {
namespace assignment1 {

class VedioProcessor {
 public:
  explicit VedioProcessor(const std::string &input_video_path,
                          const std::string &output_video_path,
                          const std::string &window_name = "video");
  ~VedioProcessor() {
    video_capture_.release();
    cv::destroyAllWindows();
  };

  // function to play the specified vedio
  void Play(bool with_subtitles);

  // function to add subtitles on one image frame
  void AddSubtitlesOnImage(cv::Mat *image);

  // function to process the input video and image paths to construct one new
  // video
  void Process(const std::vector<cv::String> &image_paths);

 private:
  std::string input_video_path_;
  std::string output_video_path_;
  std::string window_name_;

  cv::VideoCapture video_capture_;
  cv::VideoWriter video_writer_;
  cv::Mat image_;

  double frame_rate_;
  double frame_count_;
};

}  // namespace assignment1
}  // namespace cv_project

#endif
