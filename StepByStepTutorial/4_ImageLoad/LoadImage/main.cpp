#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    Mat image;
    Mat dst, src;
    try
    {
        image = imread("\\GrayItem.jpg", IMREAD_COLOR);

        if(!image.data )                              // Check for invalid input
           {
               cout <<  "Could not open or find the image" << std::endl ;
               return -1;
           }

        namedWindow("Input image", CV_WINDOW_AUTOSIZE);
        imshow("Input image", image);


        image.convertTo(dst,CV_32F);
        namedWindow("Dst image", CV_WINDOW_AUTOSIZE);
        imshow("Dst image", dst);
    }
    catch(...)
    {
        cout << "Problem!" << endl;
    }

    cout << "pixel depth: " << image.depth() << std::endl ;
    cout << "image height: " << image.size().height << std::endl;
    cout << "image width: " << image.size().width << std::endl;
    cout << "image channels: " << image.channels() << std::endl;
    cout << "image depth: " << dst.depth() << std::endl;

    cvWaitKey(0);

    return 0;
}
