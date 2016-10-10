#include <iostream>
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

//    if( argc != 2)
//    {
//     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
//     return -1;
//    }

    Mat image;
    image = imread("\\image.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow("Display window", WINDOW_NORMAL | WINDOW_KEEPRATIO);
    imshow("Display window", image );

    waitKey(0);
    return 0;
}
