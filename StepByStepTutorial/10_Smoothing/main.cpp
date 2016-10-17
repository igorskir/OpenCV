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
int HomogeneousSmoothing(Mat srcImage);
Mat LoadImage(string imgPath);
int ShowImageHistogram(Mat image);


int main(int argc, char *argv[])
{

    Mat inputImage = LoadImage("..\\InputImages\\girl.jpg");

    if( HomogeneousSmoothing(inputImage) != 0 ) { return 0; }


    waitKey(0);
    return 0;
}


Mat LoadImage(string imgPath)
{
    Mat src = imread(imgPath, IMREAD_COLOR);

    if(!src.data )                              // Check for invalid input
       {
           cout <<  "Could not open or find the image" << std::endl ;
           return src;
       }

    return src;

}

int HomogeneousSmoothing(Mat srcImage)
{
    namedWindow("Original image", WINDOW_AUTOSIZE);

    imshow("Original image",srcImage);

    Mat dstImage;

    string tempText;
    string strName;

    for (int i = 1; i <= MAX_KERNEL_LENGTH; i=i+2)
    {
        tempText = "Kernel Size: " +  std::to_string(i) + " x " + std::to_string(i);

        blur(srcImage,dstImage,Size(i,i));

        if( DisplayImage(dstImage,"Smoothed image", tempText, DELAY_CAPTION)) { return 0; }

        //ShowImageHistogram(dstImage);

        strName = "Images\\Image_Kernel_" + std::to_string(i) + "px.jpg";

        imwrite( strName, dstImage );
    }
    return 0;
}

int DisplayImage(Mat dstImage, string windowName = "Window", string windowText = "", int delay = 0)
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

int ShowImageHistogram(Mat image)
{
    if(!image.data )                              // Check for invalid input
       {
           cout <<  "Could not open or find the image" << std::endl ;
           return -1;
       }

    Mat dst;

    vector<Mat> bgrPlanes;
    split(image, bgrPlanes);

    int histSize = 256;

    float range[] = {0, 256};
    const float *histRange  = { range };

    bool uniform = true;
    bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    calcHist( &bgrPlanes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgrPlanes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgrPlanes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  );
    }

    DisplayImage(histImage, "calcHist Demo", "", 0);

    return 0;
}




