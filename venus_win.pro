#-------------------------------------------------
#
# Project created by QtCreator 2018-11-10T08:07:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

QT_CONFIG -= no-pkg-config
#CONFIG  += link_pkgconfig
#PKGCONFIG += opencv

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    imagedisplaylabel.cpp \
    imageviewlistwidget.cpp \
    imageviewlistwidgetitem.cpp \
    patternsave.cpp

HEADERS += \
        mainwindow.h \
    imagedisplaylabel.h \
    imageviewlistwidget.h \
    imageviewlistwidgetitem.h \
    patternsave.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += D:\opencv\opencv\build\include
INCLUDEPATH += "C:\Program Files\Tesseract-OCR\include\tesseract"
#INCLUDEPATH += "C:\Program Files\Tesseract-OCR\include\leptonica"
LIBS += D:\opencv\opencv-build\bin\libopencv_core400.dll
LIBS += D:\opencv\opencv-build\bin\libopencv_highgui400.dll
LIBS += D:\opencv\opencv-build\bin\libopencv_imgcodecs400.dll
LIBS += D:\opencv\opencv-build\bin\libopencv_imgproc400.dll
LIBS += D:\opencv\opencv-build\bin\libopencv_features2d400.dll
LIBS += D:\opencv\opencv-build\bin\libopencv_calib3d400.dll
LIBS += D:\opencv\opencv-build\bin\libopencv_video400.dll
LIBS += D:\opencv\opencv-build\bin\libopencv_videoio400.dll

#LIBS += "C:\Program Files\Tesseract-OCR\libtesseract-4.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\zlib1.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libgcc_s_sjlj-1.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libgif-7.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libtesseract-4.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libtesseract-4.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libtesseract-4.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libtesseract-4.dll"

#LIBS += G:\venus\lib\zlib1.dll
#LIBS += G:\venus\lib\libgcc_s_sjlj-1.dll
#LIBS += G:\venus\lib\libgif-7.dll
#LIBS += G:\venus\lib\libjbig-2.dll
#LIBS += G:\venus\lib\libjpeg-8.dll
#LIBS += G:\venus\lib\liblept-5.dll
#LIBS += G:\venus\lib\liblzma-5.dll
#LIBS += G:\venus\lib\libopenjp2-7.dll
#LIBS += G:\venus\lib\libpng16-16.dll
#LIBS += G:\venus\lib\libtesseract-4.dll
#LIBS += G:\venus\lib\libtiff-5.dll
#LIBS += G:\venus\lib\libwebp-7.dll
LIBS += C:\Tesseract-SDK\lib\libtesseract-4.dll

#LIBS += G:\venus\release\zlib1.dll
#LIBS += G:\venus\release\libgcc_s_sjlj-1.dll
#LIBS += G:\venus\release\libgif-7.dll
#LIBS += G:\venus\release\libjbig-2.dll
#LIBS += G:\venus\release\libjpeg-8.dll
#LIBS += G:\venus\release\liblept-5.dll
#LIBS += G:\venus\release\liblzma-5.dll
#LIBS += G:\venus\release\libopenjp2-7.dll
#LIBS += G:\venus\release\libpng16-16.dll
#LIBS += G:\venus\release\libtesseract-4.dll
#LIBS += G:\venus\release\libtiff-5.dll
#LIBS += G:\venus\release\libwebp-7.dll

#LIBS += "C:\Program Files\Tesseract-OCR\zlib1.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libgcc_s_sjlj-1.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libgif-7.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libjbig-2.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libjpeg-8.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\liblept-5.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\liblzma-5.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libopenjp2-7.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libpng16-16.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libtesseract-4.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libtiff-5.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libwebp-7.dll"

#LIBS += "C:\Program Files\Tesseract-OCR\zlib1.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libgcc_s_sjlj-1.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libgif-7.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libjbig-2.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libjpeg-8.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\liblept-5.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\liblzma-5.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libopenjp2-7.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libpng16-16.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libtesseract-4.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libtiff-5.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\libwebp-7.dll"

#LIBS += G:\venus\lib_new\zlib1.dll
#LIBS += G:\venus\lib_new\libgcc_s_dw2-1.dll
#LIBS += G:\venus\lib_new\libgif-7.dll
#LIBS += G:\venus\lib_new\libjpeg-8.dll
#LIBS += G:\venus\lib_new\liblept-5.dll
#LIBS += G:\venus\lib_new\liblzma-5.dll
#LIBS += G:\venus\lib_new\libopenjp2-7.dll
#LIBS += G:\venus\lib_new\libpng16-16.dll
#LIBS += G:\venus\lib_new\libtesseract-4.dll
#LIBS += G:\venus\lib_new\libtiff-5.dll
#LIBS += G:\venus\lib_new\libwebp-7.dll
#LIBS += G:\venus\lib_new\libzstd.dll


#LIBS += "C:\Program Files\Tesseract-OCR\lib\libtesseract-4.dll"
#LIBS += "C:\Program Files\Tesseract-OCR\lib\libtesseract-4.a"


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
