#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  cv::Mat image;
  cv::Mat imagetroc;

  image= cv::imread("biel.png",cv::IMREAD_GRAYSCALE);
  imagetroc= cv::imread("biel.png",cv::IMREAD_GRAYSCALE);

  if(!image.data)
    std::cout << "nao abriu bolhas.png" << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);


  int altura = image.size().height;
  int largura = image.size().width;

  for(int i=0; i< image.size().height/2; i++){
    for(int j=0; j< image.size().width/2; j++){
      imagetroc.at<uchar>(i,j)=image.at<uchar>(i+(altura/2),j+(largura/2));
      imagetroc.at<uchar>(i+(altura/2),j+(largura/2)-1)=image.at<uchar>(i,j);
    }
  }
  for(int i=0; i< image.size().height/2; i++){
    for(int j=largura/2; j< largura; j++){
      imagetroc.at<uchar>(i,j)=image.at<uchar>(i+(altura/2),j-(largura/2));
      imagetroc.at<uchar>(i+(altura/2),j-(largura/2))=image.at<uchar>(i,j);
    }
  }
  imwrite("trocaregioes.png", imagetroc);
  imshow("janela", imagetroc);
  waitKey();

  return 0;
}
