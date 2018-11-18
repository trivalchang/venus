#ifndef IMAGEDISPLAYLABEL_H
#define IMAGEDISPLAYLABEL_H

#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

class ImageDisplayLabel:public QLabel
{
public:
    ImageDisplayLabel(QWidget *parent = NULL, Qt::WindowFlags f=0);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void displayImage(QImage imgToDraw);
    void enableDrawROI(bool benable);
    void getROI(QRect &rect);
    void displayImage(cv::Mat img);
protected:
    void paintEvent(QPaintEvent *event);
private:
    bool m_bDrawROI;
    QImage m_imgToDraw;
    QPoint m_ROIStart;
    QPoint m_ROIEnd;
};

#endif // IMAGEDISPLAYLABEL_H
