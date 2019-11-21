#ifndef COMPUTER_VISION_ASSIGNMENTS_VEDIO_PROCESSOR_H_
#define COMPUTER_VISION_ASSIGNMENTS_VEDIO_PROCESSOR_H_

#include <opencv2/opencv.hpp>

namespace cv_project {
namespace assignment1 {

class VedioProcessor {
 public:
  explicit VedioProcessor(const std::string &vedio_path,
                          const std::string &window_name = "video");
  ~VedioProcessor() {
    video_capture_.release();
    cv::destroyAllWindows();
  };

  // function to play the specified vedio
  void Play(bool with_subtitles);

 private:
  std::string video_path_;
  std::string window_name_;

  cv::VideoCapture video_capture_;
  cv::Mat image_;

  double frame_rate_;
  double frame_count_;
};

}  // namespace assignment1
}  // namespace cv_project

#endif
