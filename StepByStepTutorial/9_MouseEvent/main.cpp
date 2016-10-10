#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


void drawTarget(Mat img, int x, int y, int radius)
{
    circle(img,Point(x,y), radius, CV_RGB(260,0,0));
    line(img, Point(x-radius/2, y-radius/2), Point(x+radius/2, y+radius/2),CV_RGB(260,0,0));
    line(img, Point(x+radius/2, y-radius/2), Point(x-radius/2, y+radius/2),CV_RGB(260,0,0));
}

void myMouseCallback(int event, int x, int y, int flags, void *param)
{
    //Mat img = (Mat) &param;
    Mat img = *((Mat*) param);
    switch(event)
    {
        case CV_EVENT_MOUSEMOVE:
            break;
        case CV_EVENT_LBUTTONDOWN:
            cout << x << " x " << y << endl;
            drawTarget(img,x,y,10);
            break;
        case CV_EVENT_LBUTTONUP:
            break;
    }
}

int main(int argc, char *argv[])
{
    Mat image;
    Mat imageClone;


    try
    {
        image = imread("\\cat.jpg", IMREAD_COLOR);

        if(!image.data )                              // Check for invalid input
           {
               cout <<  "Could not open or find the image" << std::endl ;
               return -1;
           }
        imageClone = image.clone();

        namedWindow("Input image", CV_WINDOW_AUTOSIZE);
        setMouseCallback("Input image", myMouseCallback, (void*) &image);

        while(1)
        {
            //imageClone =  image;
            imshow("Input image", image);

            char c = cvWaitKey(33);
            if (c == 27)
            { // если нажата ESC - выходим
                break;
            }
        }
    }
    catch(...)
    {
        cout << "Problem!" << endl;
    }

    return 0;
}
