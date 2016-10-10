#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat image;
    image = imread("\\image.jpg", IMREAD_COLOR);

//    if( argc != 2 || !image.data )
//    {
//      printf( " No image data \n " );
//      return -1;
//    }

    Mat grayImage;
    cvtColor(image,grayImage, CV_BGR2GRAY);

    imwrite("\\GrayItem.jpg",grayImage);

    namedWindow("Input image", CV_WINDOW_AUTOSIZE);
    namedWindow("Gray image", CV_WINDOW_AUTOSIZE);

    imshow("Input image", image);
    imshow("Gray image", grayImage);

    cvWaitKey(0);

    return 0;
}
