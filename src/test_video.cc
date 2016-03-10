#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc,char* argv[]){

  cv::VideoCapture capture(argv[2]);
  if(!capture.isOpened()){
    std::cout<<"fail to open!"<<std::endl;
    fprintf(stderr,"-1");
    return -1;
  }
  //get video information.
  int totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
  std::cout<<"Total Frame Number:"<<totalFrameNumber<<std::endl;
  int fps = capture.get(CV_CAP_PROP_FPS);
  int frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
  int frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
  cv::Mat frame;
  //get frame position.
  std::ifstream pos_in(argv[5]);                              
  char c_pos[10];                                             
  pos_in>>c_pos;                                              
  int i_pos = atoi(c_pos);                                                 
  pos_in.close(); 
  //set frame position.
  capture.set(CV_CAP_PROP_POS_FRAMES,i_pos+1);
  while(1){
    if(!capture.read(frame)){  
      //output current frame position.                               
      std::ofstream pos_file(argv[5],std::ios::out);          
      pos_file<<(int)video_input.get(CV_CAP_PROP_POS_FRAMES); 
      pos_file.close();                                       
      return 0;                                               
    }
    //video process.
  }
  return 1;
}
