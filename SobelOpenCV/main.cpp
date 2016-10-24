#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace std;
using namespace cv;

Mat LoadImage(string imgPath);
void writeMatToFile(Mat &m, const char *filename);
void writeMatToFileOpenCV(Mat &m, const char *filename);
void mySobelOperator(const Mat &img);

int main(int argc, char *argv[])
{
    Mat srcImage = LoadImage("..\\SrcImages\\11.jpg");

    namedWindow("Original image", WINDOW_AUTOSIZE);
    imshow("Original image",srcImage);

    double t;
    t = (double)getTickCount();

    mySobelOperator(srcImage);

    t = 1000*((double)getTickCount() - t)/getTickFrequency();

    cout << "Time of Filter 2d mat operations = " << t << " milliseconds."<< endl;


    waitKey();
    return 0;
}

void mySobelOperator(const Mat& img)
{
    Mat grey;
    //cvtColor(img, grey, COLOR_BGR2GRAY);
    Mat sobelx;
    Sobel(img, sobelx, CV_32F, 1, 0, 13);

    double minVal, maxVal;
    minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
    Mat draw;
    sobelx.convertTo(draw,CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));

    namedWindow("Sobel image", WINDOW_AUTOSIZE);
    imshow("Sobel image", draw);

}

Mat LoadImage(string imgPath)
{
    Mat src = imread(imgPath, IMREAD_GRAYSCALE);

    if(!src.data )                              // Check for invalid input
       {
           cout <<  "Could not open or find the image" << std::endl ;
           return src;
       }

    return src;

}

void writeMatToFile(cv::Mat& m, const char* filename)
{
    ofstream fout(filename);

    if(!fout)
    {
        cout<<"File Not Opened"<<endl;  return;
    }

    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
        {
            fout<<(int)m.at<uchar>(i,j)<<"\t";
        }
        fout<<endl;
    }

    fout.close();
}

void writeMatToFileOpenCV(Mat& m, const char* filename)
{
    cv::FileStorage file(filename, FileStorage::WRITE);

    // Write to file!
    file << "matName" << m;

    //read somethingg
//    Mat myMatrix2;
//    FileStorage fs2("test.xml", FileStorage::READ);
//    fs2["myMatrix"] >> myMatrix2;
//    fs2.release();
}
