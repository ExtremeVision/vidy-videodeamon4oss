#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc,char* argv[]){

  cv::VideoCapture capture(argv[1]);
  if(!capture.isOpened()){
    std::cout<<"-1"<<std::endl;
    return -1;
  }
  int totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
  std::cout<<totalFrameNumber<<std::endl;
  return 1;
}
