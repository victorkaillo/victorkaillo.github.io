#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  cv::Mat image, realce;
  int width, height;
  int nobjects, noburacos;
  
  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }

  width=image.cols;
  height=image.rows;
  std::cout << width << "x" << height << std::endl;

  p.x=0;
  p.y=0;

  for(int i=0; i<height; i++){
    if(image.at<uchar>(0, i) == 255){ 
        floodFill(image,Point(i, 0), 0); /*exclui bolhas da primeira linha */
    }
    if(image.at<uchar>(width-1, i) == 255){ 
        floodFill(image,Point(i, width-1), 0); /*exclui bolhas da ultima linha*/
    }
  } 

  for(int i=0; i<width; i++){
    if(image.at<uchar>(i,0) == 255){ 
        floodFill(image,Point(0, i), 0); /*exuclui bolhas da primeira coluna*/
    }
    if(image.at<uchar>(i,height-1) == 255){ 
        floodFill(image,Point(height-1, i), 0); /*exclui bolhas da ultima coluna*/
    }
  }

  // busca objetos presentes
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
        // achou um objeto
        nobjects++;
        p.x=j;
        p.y=i;
  		/* preenche o objeto com 0 (asssim perdemos a saida com identificacao mas conseguimos contar normalmente o numero de bolhas mesmo com numero maior que 255)*/
		  cv::floodFill(image,p,nobjects);
      }
    }
  }
    //cv::imshow("image0", image);

  /*fundo branco*/

  floodFill(image,Point(0,0),255);


  /**/
  noburacos = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 0 && (int)image.at<uchar>(i,j-1)>noburacos){
        /*achou buraco*/
        noburacos++;
        p.x=j;
        p.y=i;
        floodFill(image,p,255);
      }
    }
  }

  floodFill(image,Point(0,0),0);

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
        // achou um objeto
        //nobjects++;
        p.x=j;
        p.y=i;
      /* preenche o objeto com 0 (asssim perdemos a saida com identificacao mas conseguimos contar normalmente o numero de bolhas mesmo com numero maior que 255)*/
      cv::floodFill(image,p,150);
      }
    }
  }
    floodFill(image,Point(0,0),255);

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 150){
        // achou um objeto
        //nobjects++;
        p.x=j;
        p.y=i;
      /* preenche o objeto com 0 (asssim perdemos a saida com identificacao mas conseguimos contar normalmente o numero de bolhas mesmo com numero maior que 255)*/
      cv::floodFill(image,p,0);
      }
    }
  }


  std::cout << "a figura tem " << nobjects << " bolhas\n";
  std::cout << "a figura tem ao menos " << noburacos << " bolhas com buracos {nao consideramos eventuais buracos nas extremidades}\n";
  cv::equalizeHist(image, realce);
  cv::imshow("image", image);
  cv::imshow("realce", realce);
  cv::imwrite("labeling_extremidade.png", image);
  //cv::imwrite("labeling_extremidade_realce.png", realce);
  cv::waitKey();
  return 0;
}
