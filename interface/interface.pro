#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T15:22:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    harris.h

FORMS    += mainwindow.ui
INCLUDEPATH+=C:\OpencvQt\OpenCV\include\opencv\
                    C:\OpencvQt\OpenCV\include\opencv2\
                    C:\OpencvQt\OpenCV\include
LIBS+=C:\OpencvQt\OpenCV\lib\libopencv_calib3d249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_contrib249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_core249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_features2d249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_flann249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_gpu249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_highgui249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_imgproc249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_legacy249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_ml249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_objdetect249.dll.a\
        C:\OpencvQt\OpenCV\lib\libopencv_video249.dll.a
