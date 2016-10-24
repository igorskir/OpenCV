#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpenFile_clicked()
{
    QString strFileName = QFileDialog::getOpenFileName(this, tr("Open image file"),
                                                      "..//",
                                                      tr("Images (*.png *.xpm *.jpg)"));

    if(strFileName.isEmpty())
    {
        ui->lblChosenFile->setText("file not chosen");
        return;
    }

    cv::Mat imgOriginal;            // input image
    cv::Mat imgGrayscale;           // grayscale of input image
    cv::Mat imgBlurred;             // intermediate blured image
    cv::Mat imgCanny;               // Canny edge image

    imgOriginal = cv::imread(strFileName.toStdString(),cv::IMREAD_GRAYSCALE);

    if (imgOriginal.empty()) {									// if unable to open image
        ui->lblChosenFile->setText("error: image not read from file");      // update lable with error message
        return;                                                             // and exit function
    }

    ui->lblChosenFile->setText(strFileName);

    cv::bilateralFilter(imgOriginal,imgBlurred, 13,60,60);
    cv::Canny(imgBlurred,imgCanny,45,150);

    QImage qimgOriginal = convertOpenCVMatToQtQImage(imgOriginal);
    QImage qimgBlurred = convertOpenCVMatToQtQImage(imgBlurred);
    QImage qimCanny = convertOpenCVMatToQtQImage(imgCanny);

    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->lblCanny->setPixmap(QPixmap::fromImage(qimCanny));


}

QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat)
{
    if(mat.channels() == 1)
    {
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
    }
    else
    {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }

    return QImage();

}

