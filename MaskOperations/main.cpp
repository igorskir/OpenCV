#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace std;
using namespace cv;

Mat LoadImage(string imgPath);
void Sharpen(const Mat &myImage, Mat &result);
void Sharpen2DFilter(const Mat &myImage, Mat &result, const Mat &kernel);
void writeMatToFile(Mat &m, const char *filename);
void writeMatToFileOpenCV(Mat &m, const char *filename);

int main(int argc, char *argv[])
{
    Mat srcImage = LoadImage("..\\SrcImages\\1.jpg");

    namedWindow("Original image", WINDOW_AUTOSIZE);
    imshow("Original image",srcImage);

    writeMatToFile(srcImage, "..\\SrcImages\\out.txt");

    writeMatToFileOpenCV(srcImage, "..\\SrcImages\\outOpenCV.xml");

    double minVal, maxVal;
    minMaxLoc(srcImage, &minVal, &maxVal); //find minimum and maximum intensities
    cout << "Min value =" << minVal <<endl << "Max value =" << maxVal << endl;

    Mat result;
    const int times = 100;
    double t;

    Mat kern = (Mat_<char>(3,3) <<  0, -1,  0,
                                   -1,  5, -1,
                                    0, -1,  0);

    t = (double)getTickCount();

    Sharpen2DFilter(srcImage,result,kern);

    t = 1000*((double)getTickCount() - t)/getTickFrequency();

    cout << "Time of Filter 2d mat operations (averaged for "
             << times << " runs): " << t << " milliseconds."<< endl;

    namedWindow("Filter2D result image", WINDOW_AUTOSIZE);
    imshow("Filter2D result image",result);



    t = (double)getTickCount();

    Sharpen(srcImage, result);

    t = 1000*((double)getTickCount() - t)/getTickFrequency();

    cout << "Time of mat operations (averaged for "
             << times << " runs): " << t << " milliseconds."<< endl;

    namedWindow("Result image", WINDOW_AUTOSIZE);
    imshow("Result image",result);



    waitKey();

    return 0;
}


void Sharpen(const Mat& myImage, Mat& result)
{
    CV_Assert(myImage.depth() == CV_8U);
    result.create(myImage.size(), myImage.type());

    const int nChannels = myImage.channels();

    for (int j = 1; j < myImage.rows - 1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);

        uchar* output = result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels * (myImage.cols - 1) ; ++i)
        {
            *output++ = saturate_cast<uchar>(5 * current[i]
                                     -current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
        }
    }

    result.row(0).setTo(Scalar(0));
    result.row(result.rows - 1).setTo(Scalar(0));
    result.col(0).setTo(Scalar(0));
    result.col(result.cols - 1).setTo(Scalar(0));

}

void Sharpen2DFilter(const Mat& myImage, Mat& result, const Mat& kernel)
{
    filter2D(myImage, result, myImage.depth(), kernel);
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
