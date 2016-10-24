#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace std;
using namespace cv;

/// Global Variables
int DELAY_CAPTION = 2000;

/// Function headers
int DisplayImage(const Mat &dstImage, string windowName, string windowText, int delay);
Mat LoadImage(string imgPath);
int ShowImageHistogram(Mat image);
void ShowMenu();

void StartImageProcessing(const Mat& srcImage);
int HomogeneousSmoothing(const Mat &srcImage, int ksize);
int GaussianSmoothing(const Mat& srcImage, int ksize);
int MedianSmoothing(const Mat &srcImage, int ksize);
int BilateralSmoothing(const Mat &srcImage, int ksize);



int main(int argc, char *argv[])
{
    cout << "Hello! It's image smoothing programm!" << endl;
    cout << "-------------------------------------" << endl;

    char choice = '4';
    Mat srcImage;
    do
    {
        switch(choice)
        {
            case '1':
                srcImage = LoadImage("..\\InputImages\\cat.jpg");
                break;


            case '2':
                DisplayImage(srcImage,"Original image","",1);
                waitKey();
                break;

            case '3':
                StartImageProcessing(srcImage);
                break;

            case '4':
                ShowMenu();
                break;

            case '5':
                return 0;
                break;

            default:
                cout << "You've chosen incorrect number." << endl;
                cout << "Do you want close app? Y/N:";
                char isQuit;
                cin >> isQuit;
                if (isQuit == 'Y' || isQuit =='y')
                    return 0;
                break;
        }
        cout << "Enter your selection: ";
        cin >> choice;
    } while (choice != '5');

    waitKey(0);
    return 0;
}


void StartImageProcessing(const Mat& srcImage)
{
    if(!srcImage.data )                              // Check for invalid input
       {
           cout <<  "Sorry, could not open or find the source image" << endl ;
           return;
       }


    int ksize = 3;
    cout << "\nChoose method please:" << endl
         << "1. Homogeneous Smoothing;" << endl
         << "2. Gaussian Smoothing;" << endl
         << "3. Median Smoothing;" << endl
         << "4. Bilateral Smoothing;" << endl;

    char mchoice;

    cout << "Enter filter nubmer please: ";
    cin >> mchoice;

    switch(mchoice)
    {
        case '1':
            cout << "Input the kernel size plese: (odd number) ";
            cin >> ksize;
            if (ksize %2 == 0)
            {
                cout << "Bad input data. Kernel size must be odd" <<endl;
                break;
            }
            HomogeneousSmoothing(srcImage, ksize);
            break;

        case '2':
            cout << "Input the kernel size plese: (odd number) ";
            cin >> ksize;
            if (ksize %2 == 0)
            {
                cout << "Bad input data. Kernel size must be odd" <<endl;
                break;
            }
            GaussianSmoothing(srcImage,ksize);
            break;

        case '3':
            cout << "Input the kernel size plese: (odd number) ";
            cin >> ksize;
            if (ksize %2 == 0)
            {
                cout << "Bad input data. Kernel size must be odd" <<endl;
                break;
            }
            MedianSmoothing(srcImage, ksize);
            break;

        case '4':
            cout << "Input the kernel size plese: (odd number) ";
            cin >> ksize;
            if (ksize %2 == 0)
            {
                cout << "Bad input data. Kernel size must be odd" <<endl;
                break;
            }
            BilateralSmoothing(srcImage, ksize);
            break;

        default:
            cout << "You've chosen incorrect number." << endl;
            break;
    }
}

Mat LoadImage(string imgPath)
{
    Mat src = imread(imgPath, IMREAD_COLOR);

    if(!src.data )                              // Check for invalid input
       {
           cout <<  "Could not open or find the image" << std::endl ;
           return src;
       }

    cout << "The image is successfully loaded!" << endl;
    return src;
}

int HomogeneousSmoothing(const Mat& srcImage, int ksize)
{
    Mat dstImage;

    string headerText;
    string strName;
    string strKernSize = std::to_string(ksize);

//    for (int i = 1; i <= MAX_KERNEL_LENGTH; i=i+2)
//    {

    headerText = "Kernel Size: " +  strKernSize + " x " + strKernSize;

    blur(srcImage,dstImage,Size(ksize,ksize));

    DisplayImage(dstImage,"Smoothed image", headerText, 1);

    //ShowImageHistogram(dstImage);

    strName = "Images\\homo_kern_" + strKernSize + "px.jpg";

    imwrite( strName, dstImage );
    cout << "Image was succesfully writed to disk! File name: " << strName << endl;

//    }
    return 0;
}

int GaussianSmoothing(const Mat &srcImage, int ksize)
{
    Mat dstImage;

    string headerText;
    string strName;
    string strKernSize = std::to_string(ksize);

//    for (int i = 1; i <= MAX_KERNEL_LENGTH; i=i+2)
//    {

    headerText = "Kernel Size: " +  strKernSize + " x " + strKernSize;

    GaussianBlur(srcImage,dstImage,Size(ksize,ksize),0,0);

    DisplayImage(dstImage,"Gaussian smoothed image", headerText, 1);

    //ShowImageHistogram(dstImage);

    strName = "Images\\Gaus_kern_" + strKernSize + "px.jpg";

    imwrite( strName, dstImage );
    cout << "Image was succesfully writed to disk! File name: " << strName << endl;
//    }
    return 0;
}

int MedianSmoothing(const Mat &srcImage, int ksize)
{
    Mat dstImage;

    string headerText;
    string strName;
    string strKernSize = std::to_string(ksize);

//    for (int i = 1; i <= MAX_KERNEL_LENGTH; i=i+2)
//    {

    headerText = "Kernel Size: " +  strKernSize + " x " + strKernSize;

    medianBlur(srcImage,dstImage,ksize);

    DisplayImage(dstImage,"Median smoothed image", headerText, 1);

    //ShowImageHistogram(dstImage);

    strName = "Images\\median_kern_" + strKernSize + "px.jpg";

    imwrite( strName, dstImage );
    cout << "Image was succesfully writed to disk! File name: " << strName << endl;
//    }
    return 0;
}

int BilateralSmoothing(const Mat &srcImage, int ksize)
{
    Mat dstImage;

    string headerText;
    string strName;
    string strKernSize = std::to_string(ksize);

//    for (int i = 1; i <= MAX_KERNEL_LENGTH; i=i+2)
//    {

    headerText = "Kernel Size: " +  strKernSize + " x " + strKernSize;

    const uint Sr = 90;
    bilateralFilter(srcImage,dstImage,ksize,Sr,Sr);

    DisplayImage(dstImage,"Bilateral smoothed image", headerText, 1);

    //ShowImageHistogram(dstImage);

    strName = "Images\\bilat_kern_" + strKernSize + "Sr="+ std::to_string(Sr)+ "px.jpg";

    imwrite( strName, dstImage );
    cout << "Image was succesfully writed to disk! File name: " << strName << endl;
//    }
    return 0;
}


int DisplayImage(const Mat& dstImage, string windowName = "Window", string windowText = "", int delay = 0)
{
    if(!dstImage.data )                              // Check for invalid input
       {
           cout <<  "Could not open or find the image" << std::endl ;
           return -1;
       }

    namedWindow(windowName, WINDOW_AUTOSIZE);

    putText(dstImage,windowText,Point(dstImage.cols/4,dstImage.rows/8), CV_FONT_HERSHEY_COMPLEX, 0.5, Scalar(255,255,255));

    imshow(windowName, dstImage);
    //waitKey( delay );
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


void ShowMenu()
{
    cout << "\nChoose the operation number please:" << endl
         << "1. Load image from disk;" << endl
         << "2. Show original image;" << endl
         << "3. Apply smooothing filter;" << endl
         << "4. Show menu;" << endl
         << "5. Quit." << endl
         << "-----------------------------------" << endl;
}



