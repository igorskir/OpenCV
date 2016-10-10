#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace std;
using namespace cv;

/// Global Variables
int DELAY_CAPTION = 2000;
int MAX_KERNEL_LENGTH = 21;

/// Function headers
int DisplayImage(Mat dstImage, string windowName, string windowText, int delay);
int HomogeneousSmoothing(string imgPath);

int main(int argc, char *argv[])
{
    if( HomogeneousSmoothing("\\cat.jpg") != 0 ) { return 0; }

    waitKey(0);
    return 0;
}

int HomogeneousSmoothing(string imgPath)
{
    namedWindow("Original image", WINDOW_AUTOSIZE);
    Mat src = imread(imgPath, IMREAD_COLOR);

    if(!src.data )                              // Check for invalid input
       {
           cout <<  "Could not open or find the image" << std::endl ;
           return -1;
       }

    imshow("Original image",src);

    Mat dst;

    string tempText;

    for (int i = 1; i < MAX_KERNEL_LENGTH; i=i+2)
    {
        tempText = "Kernel Size: " +  std::to_string(i) + " x " + std::to_string(i);

        blur(src,dst,Size(i,i));

        if( DisplayImage(dst,"Smoothed image", tempText, DELAY_CAPTION)) { return 0; }
    }
    return 0;
}

int DisplayImage(Mat dstImage, string windowName, string windowText,int delay)
{
    if(!dstImage.data )                              // Check for invalid input
       {
           cout <<  "Could not open or find the image" << std::endl ;
           return -1;
       }

    namedWindow(windowName, WINDOW_AUTOSIZE);

    putText(dstImage,windowText,Point(dstImage.cols/4,dstImage.rows/8), CV_FONT_HERSHEY_COMPLEX, 0.5, Scalar(255,255,255));

    imshow(windowName, dstImage);
    int c = waitKey( delay );
    if (c >=0) {return -1;}

    return 0;
}




