#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  cv::Mat image;
  cv::Vec3b val;

  image= cv::imread("biel.png",cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu bolhas.png" << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  int x1, x2, y1, y2;

  cout << "O tamanho da imagem é: ";
  cout << image.size().height << "/"<< image.size().width << endl;
  cout << "Escreva pontos dentro desse limite."<< endl;

  cout << "digite o x do primeiro par ordenado:" << endl;
  cin >> x1;
  cout << "digite o y do primeiro par ordenado:" << endl;
  cin >> y1;
  cout << "digite o x do segundo par ordenado:" << endl;
  cin >> x2;
  cout << "digite o y do segundo par ordenado:" << endl;
  cin >> y2;



  /*for(int i=200;i<210;i++){
    for(int j=10;j<200;j++){
      image.at<uchar>(i,j)=0;
    }
  }
  
  cv::imshow("janela", image);  
  cv::waitKey(0);*/
  //cv::waitKey();

  //image= cv::imread("bolhas.png",cv::IMREAD_COLOR);
/*
  val[0] = 0;   //B
  val[1] = 255;   //G
  val[2] = 0; //R
  
  for(int i=200;i<210;i++){
    for(int j=10;j<200;j++){
      image.at<Vec3b>(i,j)=val;
    }
  }

  cv::imshow("janela", image);  
  cv::waitKey(0);*/

  for(int i=x1; i< x2; i++){
    for(int j=y1; j< y2; j++){
      image.at<uchar>(i,j)=255-image.at<uchar>(i,j);
    }
  }

  imwrite("regioes.png", image);
  imshow("janela", image);
  waitKey();



  //cv::waitKey(-1);
  return 0;
}
