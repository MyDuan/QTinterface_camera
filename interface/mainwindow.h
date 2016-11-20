#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QLayout>
#include <QWidget>
#include <opencv.hpp>
using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateImage();
    void on_pushButton_clicked();

private:
    QTimer theTimer;
    Mat srcImage;
    IplImage iplimage;
    CvMat *intrinsics; //内参矩阵
    CvMat *distortion_coeff; //畸变矩阵
    VideoCapture videoCap;
    IplImage* mapx;
    IplImage* mapy;
    Ui::MainWindow *ui;

private:
    //double getNextMinLoc(IplImage *result, CvPoint *minLoc, int maxVaule, int templatW, int templatH);
   bool findTheCircal();
protected:
    void paintEvent(QPaintEvent *e);  
};

#endif // MAINWINDOW_H
