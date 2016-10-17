#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace std;
using namespace cv;

void WorkWithMat();
Mat& ScanImageAndReduceC(Mat &I, const uchar * const table);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if( argc == 4 && !strcmp(argv[3],"G") )
       I = imread(argv[1], IMREAD_GRAYSCALE);
    else
       I = imread(argv[1], IMREAD_COLOR);

    if (I.empty())
    {
       cout << "The image" << argv[1] << " could not be loaded." << endl;
       return -1;
    }

    int divideWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> divideWith;
    if (!s || !divideWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }
    uchar table[256];

       // do something ...
    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(divideWith * (i/divideWith));

    cout << "Table t = " <<endl;
    for (int i = 0; i < 256; ++i)
       cout << (int)table[i] << " ";

    const int times = 100;
    double t;

    t = (double)getTickCount();

//    for (int i = 0; i < times; ++i)
//    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i, table);
//    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
//    t /= times;

    cout << "Time of reducing with the C operator [] (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;

    namedWindow("NewWindow", WINDOW_AUTOSIZE);
    imshow("NewWindow", J);
    waitKey();

    return 0;

}

//! [scan-c]
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    cout << "I = " << I << endl << endl;

    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            cout << "p[" << j << "] = " << (int)p[j] << endl;
            p[j] = table[p[j]];
            cout << "p[" << j << "] = " << (int)p[j] << endl;
        }
    }

    cout << "I = " << I << endl << endl;
    return I;
}
//! [scan-c]

//! [scan-iterator]
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
    case 3:
        {
            MatIterator_<Vec3b> it, end;
            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    return I;
}
//! [scan-iterator]


void WorkWithMat()
{
    Mat M(2,2,CV_8UC2, Scalar(0,2));
    cout << "M = " << endl << " " << M << endl << endl;

    M.create(4,4,CV_8UC(2));
    cout << "M = " << endl  << M << endl << endl;

    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E = " << endl << E << endl << endl;

    Mat O = Mat::ones(2, 2, CV_32F);
    cout << "O = " << endl << " " << O << endl << endl;
    Mat Z = Mat::zeros(3,3, CV_8UC1);
    cout << "Z = " << endl << " " << Z << endl << endl;

    Mat C = (Mat_<double>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
    cout << "C = " << endl << " " << C << endl << endl;

    Mat R = Mat(3,2, CV_8UC3);

    randu(R,Scalar::all(0), Scalar::all(255));
    cout << "R = " << endl << " " << R << endl << endl;

    cout << "R = " << endl << " " << format(R, Formatter::FMT_CSV) << endl << endl;

    Point2f P(2,1);
    cout << "Point (2D) = " << P << endl << endl;

    vector<Point2f> vPoints(20);
    for (size_t i = 0; i < vPoints.size(); ++i)
    {
        vPoints[i] = Point2f((float)(i*5), (float) (i%7));
    }
    cout << "A vector of 2D Points =" << vPoints << endl << endl;
}
