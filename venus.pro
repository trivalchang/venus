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
DEFINES += TESSERACT_DATA=0

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv
PKGCONFIG += tesseract

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    imagedisplaylabel.cpp \
    imageviewlistwidgetitem.cpp \
    imageviewlistwidget.cpp \
    patternsave.cpp

HEADERS += \
        mainwindow.h \
    imagedisplaylabel.h \
    imageviewlistwidgetitem.h \
    imageviewlistwidget.h \
    patternsave.h

FORMS += \
        mainwindow.ui

QMAKE_CXXFLAGS += -Wno-old-style-cast

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
