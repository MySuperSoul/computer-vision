#include "computer-vision/assignments/assignment1/VideoProcessor.h"

namespace cv_project {
namespace assignment1 {

namespace {
std::string kid_info = "ID:   3160104367";
std::string kname_info = "Name: huangyifei";
double kscale = 0.8;
double kfont_scale = 1;
int kfont = cv::FONT_HERSHEY_COMPLEX;
int kthickness = 2;
int kid_diff = 70;
int kname_diff = 30;
int kframes_store = 20;
cv::Scalar kfont_color = cv::Scalar(0, 0, 255);
}  // namespace

// constructor
VideoProcessor::VideoProcessor(const std::string &input_video_path,
                               const std::string &output_video_path,
                               const std::string &window_name) {
  input_video_path_ = input_video_path;
  output_video_path_ = output_video_path;
  window_name_ = window_name;

  video_capture_.open(cv::String(input_video_path_));
  if (!video_capture_.isOpened()) {
    std::cerr << "Failed to open video: " << input_video_path_
              << ". Check if the path is right." << std::endl;
    return;
  }
  frame_rate_ = video_capture_.get(cv::CAP_PROP_FPS);
  frame_count_ = video_capture_.get(cv::CAP_PROP_FRAME_COUNT);
  frame_width_ = video_capture_.get(cv::CAP_PROP_FRAME_WIDTH);
  frame_height_ = video_capture_.get(cv::CAP_PROP_FRAME_HEIGHT);
  frame_delay_time_ = 1000.0 / frame_rate_;
  cv::namedWindow(window_name_, cv::WINDOW_AUTOSIZE);
}

// function to add subtitles on one image frame
void VideoProcessor::AddSubtitlesOnImage(cv::Mat *image) {
  double center_x = (*image).cols / 2.0;
  double image_y = (*image).rows;

  // Get text size in specified configuration
  int baseline;
  cv::Size text_size =
      cv::getTextSize(kid_info, kfont, kfont_scale, kthickness, &baseline);

  // put id info on image
  cv::putText(*image, kid_info,
              {static_cast<int>(center_x - text_size.width / 2.0),
               static_cast<int>(image_y - kid_diff)},
              kfont, kfont_scale, kfont_color, kthickness);

  // put name info on image
  cv::putText(*image, kname_info,
              {static_cast<int>(center_x - text_size.width / 2.0),
               static_cast<int>(image_y - kname_diff)},
              kfont, kfont_scale, kfont_color, kthickness);
}

// function to play the vedio specified by vedio path
void VideoProcessor::Play(bool with_subtitles) {
  double control_rate = 0.1;
  while (control_rate < frame_count_) {
    video_capture_.read(image_);
    cv::resize(image_, image_,
               cv::Size(image_.cols * kscale, image_.rows * kscale));

    if (with_subtitles) {
      AddSubtitlesOnImage(&image_);
    }

    cv::imshow(window_name_, image_);
    cv::waitKey(static_cast<int>(frame_delay_time_));

    control_rate++;
  }
  std::cout << "Video player finished." << std::endl;
}

// function to process the input video and image paths to construct one new
// video
void VideoProcessor::Process(const std::vector<cv::String> &image_paths) {
  video_writer_.open(
      output_video_path_, CV_FOURCC('X', 'V', 'I', 'D'), frame_rate_,
      {static_cast<int>(frame_width_), static_cast<int>(frame_height_)});

  if (!video_writer_.isOpened()) {
    std::cerr << "Could not open output file: " << output_video_path_
              << std::endl;
    return;
  }

  std::cout << "The output file will be stored in: " << output_video_path_
            << std::endl;

  // put images into new output video
  cv::Mat last_frame;
  for (auto path : image_paths) {
    image_ = cv::imread(path);
    cv::resize(
        image_, image_,
        {static_cast<int>(frame_width_), static_cast<int>(frame_height_)});

    // do images concat like ppt style
    if (!last_frame.empty()) {
      std::vector<cv::Mat> concat_images;
      image_processor_.GetConcatImages(last_frame, image_, &concat_images);

      for (auto v : concat_images) {
        video_writer_.write(v);
      }
    }

    // write the remaining images to video
    for (int i = 0; i < kframes_store; i++) {
      video_writer_.write(image_);
    }
    last_frame = image_;
  }

  for (int i = 0; i < frame_count_; i++) {
    video_capture_.read(image_);
    if (image_.cols == frame_width_ && image_.rows == frame_height_ &&
        image_.channels() == 3) {
      video_writer_.write(image_);
    }
  }

  std::cout << "Video convert done!" << std::endl;
  video_writer_.release();
}

}  // namespace assignment1
}  // namespace cv_project
