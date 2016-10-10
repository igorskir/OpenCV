#include "mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cv::Mat mat;
    mat = cv::imread("img.png");
    cvNamedWindow("Girl", CV_WINDOW_NORMAL);
    cv::imshow("Girl", mat );

    MainWindow w;
    w.show();



    cvWaitKey();


    return a.exec();
}
