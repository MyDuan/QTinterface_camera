#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int AngleInit = 0;
    ui->gridLayout->setMargin(3);
    ui->gridLayout->setSpacing(5);
    QLabel *lblAngle1 = new QLabel(QWidget::tr("Angle of Arm1:"));
    QLabel *lblAngle2 = new QLabel(QWidget::tr("Angle of Arm2:"));
    QLabel *lblAngle3 = new QLabel(QWidget::tr("Angle of Arm3:"));
    QLabel *lblAngle4 = new QLabel(QWidget::tr("Angle of Arm4:"));
    QLabel *lblAngle5 = new QLabel(QWidget::tr("Angle of Arm5:"));
    QLabel *lblAngle6 = new QLabel(QWidget::tr("Angle of Arm6:"));
    QLabel *lbl7 = new QLabel(QString::number(AngleInit));
    QLabel *lbl8 = new QLabel(QString::number(AngleInit));
    QLabel *lbl9 = new QLabel(QString::number(AngleInit));
    QLabel *lbl10 = new QLabel(QString::number(AngleInit));
    QLabel *lbl11 = new QLabel(QString::number(AngleInit));
    QLabel *lbl12 = new QLabel(QString::number(AngleInit));
    ui->gridLayout->addWidget(lblAngle1, 0, 0);
    ui->gridLayout->addWidget(lblAngle2, 1, 0);
    ui->gridLayout->addWidget(lblAngle3, 2, 0);
    ui->gridLayout->addWidget(lblAngle4, 3, 0);
    ui->gridLayout->addWidget(lblAngle5, 4, 0);
    ui->gridLayout->addWidget(lblAngle6, 5, 0);
    ui->gridLayout->addWidget(lbl7, 0, 1);
    ui->gridLayout->addWidget(lbl8, 1, 1);
    ui->gridLayout->addWidget(lbl9, 2, 1);
    ui->gridLayout->addWidget(lbl10, 3, 1);
    ui->gridLayout->addWidget(lbl11, 4, 1);
    ui->gridLayout->addWidget(lbl12, 5, 1);

    QLabel *lblx = new QLabel(QWidget::tr("PositionX:"));
    QLabel *lbly = new QLabel(QWidget::tr("PositionY:"));
    QLabel *lblz = new QLabel(QWidget::tr("PositionZ:"));
    QLabel *lblxNum = new QLabel(QString::number(AngleInit));
    QLabel *lblyNum = new QLabel(QString::number(AngleInit));
    QLabel *lblzNum = new QLabel(QString::number(AngleInit));
    ui->gridLayout_2->addWidget(lblx, 0, 0);
    ui->gridLayout_2->addWidget(lbly, 1, 0);
    ui->gridLayout_2->addWidget(lblz, 2, 0);
    ui->gridLayout_2->addWidget(lblxNum, 0, 1);
    ui->gridLayout_2->addWidget(lblyNum, 1, 1);
    ui->gridLayout_2->addWidget(lblzNum, 2, 1);

    if(videoCap.open(0))
    {
        srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
        theTimer.start(33);
    }
    CvSize size;
    size.height = srcImage.rows;
    size.width = srcImage.cols;
    mapx = cvCreateImage(size,IPL_DEPTH_32F,1);
    mapy = cvCreateImage(size,IPL_DEPTH_32F,1);
    intrinsics = cvCreateMat(3,3,CV_32FC1);
    distortion_coeff = cvCreateMat(1,4,CV_32FC1);
    intrinsics->data.fl[0] = 676.1182;   //fx
    intrinsics->data.fl[2] = 344.5732;   //cx
    intrinsics->data.fl[4] = 676.7106;   //fy
    intrinsics->data.fl[5] = 217.3888;   //cy

    intrinsics->data.fl[1] = 0;
    intrinsics->data.fl[3] = 0;
    intrinsics->data.fl[6] = 0;
    intrinsics->data.fl[7] = 0;
    intrinsics->data.fl[8] = 1;

    distortion_coeff->data.fl[0] = -0.5077;  //k1
    distortion_coeff->data.fl[1] = 0.3821;  //k2
    distortion_coeff->data.fl[2] = 0.0037;   //p1
    distortion_coeff->data.fl[3] = 0.0026;   //p2
    cvInitUndistortMap(intrinsics, distortion_coeff, mapx, mapy);
}
bool MainWindow::findTheCircal()
{
    int iLowH = 100;
    int iHighH = 140;
    int iLowS = 80;
    int iHighS = 255;
    int iLowV = 80;
    int iHighV = 255;
    Mat imgHSV;
    vector<Mat> hsvSplit;
    GaussianBlur(srcImage, srcImage, Size(3, 3), 0, 0);
    medianBlur(srcImage, srcImage, 3);

    cvtColor(srcImage, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    split(imgHSV, hsvSplit);
    equalizeHist(hsvSplit[2],hsvSplit[2]);
    merge(hsvSplit,imgHSV);
    Mat imgThresholded;

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

    morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
    vector<Vec3f> circles;
    GaussianBlur(imgThresholded, imgThresholded, Size(3, 3), 0, 0);
    HoughCircles(imgThresholded, circles, CV_HOUGH_GRADIENT,2, imgThresholded.rows/2, 95, 47.5, 15, 60);
    int i;
    for(i = 0; i < circles.size(); i++)
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         //draw point
         circle( srcImage, center, 3, Scalar(0,0,255), -1, 8, 0 );
         //draw circle
         circle( srcImage, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    //视屏显示
    QImage image2 = QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image2));
    ui->label->show();
}

void MainWindow::updateImage()
{
    videoCap>>srcImage;
    if(srcImage.data)
    {
        findTheCircal();
        iplimage = srcImage;
        cvRemap(&iplimage, &iplimage, mapx, mapy);
        Mat srcImage1(&iplimage);
        cvtColor(srcImage1, srcImage, CV_BGR2RGB);
        this->update();
    }
}

void MainWindow::on_pushButton_clicked()
{
    connect(&theTimer, &QTimer::timeout, this, &MainWindow::updateImage);
}
