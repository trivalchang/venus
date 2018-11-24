
#include "imagedisplaylabel.h"
#include <QtGlobal>

ImageDisplayLabel::ImageDisplayLabel(QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent,f)
    ,m_bDrawROI(false)
    ,m_ROIStart{-1,-1}
    ,m_ROIEnd{-1,-1}
{

}

void ImageDisplayLabel::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPoint invalid(-1, -1);

    paint.setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap));
    paint.drawPixmap(QPoint(0, 0), QPixmap::fromImage(m_imgToDraw));

    if ((m_ROIStart==invalid) || (m_ROIEnd==invalid))
    {
        return;
    }
    QPoint tl(qMin(m_ROIStart.x(), m_ROIEnd.x()), qMin(m_ROIStart.y(), m_ROIEnd.y()));
    QPoint br(qMax(m_ROIStart.x(), m_ROIEnd.x()), qMax(m_ROIStart.y(), m_ROIEnd.y()));
    paint.drawRect(QRect(tl, br));
}

void ImageDisplayLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bDrawROI == false)
    {
        return;
    }
    m_ROIEnd = event->pos();
    repaint();
}

void ImageDisplayLabel::mousePressEvent(QMouseEvent *event)
{
    if (m_bDrawROI == false)
    {
        return;
    }
    m_ROIStart = event->pos();
    m_ROIEnd = event->pos();
    repaint();
}

void ImageDisplayLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void ImageDisplayLabel::mouseReleaseEvent(QMouseEvent *event)
{
    printf("%s:: %d, %d\n", __FUNCTION__, event->x(), event->y());
    enableDrawROI(false);
}

void ImageDisplayLabel::displayImage(QImage imgToDraw)
{
    m_imgToDraw = imgToDraw.copy();
    repaint();
}

void ImageDisplayLabel::enableDrawROI(bool benable)
{
    if (benable == true)
    {
        QPoint invalid(-1, -1);

        m_ROIStart = invalid;
        m_ROIEnd = invalid;
    }
    setMouseTracking(benable);
    m_bDrawROI = benable;
}

void ImageDisplayLabel::getROI(QRect &rect)
{
    QPoint tl(qMin(m_ROIStart.x(), m_ROIEnd.x()), qMin(m_ROIStart.y(), m_ROIEnd.y()));
    QPoint br(qMax(m_ROIStart.x(), m_ROIEnd.x()), qMax(m_ROIStart.y(), m_ROIEnd.y()));
    rect = QRect(tl, br);
}

void ImageDisplayLabel::displayImage(cv::Mat img)
{
    int newW = 0, newH = 0;
    float imgRatio, displayRatio;

    imgRatio = float(img.cols)/float(img.rows);
    displayRatio = float(size().width())/float(size().height());
    if (imgRatio >= displayRatio)    // image ratio is wider than display widget
    {
        newW = size().width();
        newH = int(float(img.rows) * float(newW)/float(img.cols));
    }
    else if (imgRatio < displayRatio)
    {
        newH = size().height();
        newW = int(float(img.cols) * float(newH)/float(img.rows));
    }

    if ((newW != size().width()) ||
            (newH != size().height()))
    {
        resize(newW, newH);
    }

    cv::resize(img, img, cv::Size(newW, newH), 0, 0, cv::INTER_LINEAR);
    //cv::cvtColor(img,img,COLOR_BGR2RGB);
    if (img.channels() == 3)
    {
        QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        displayImage(imdisplay);
    }
    else if (img.channels() == 1)
    {
        QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        displayImage(imdisplay);
    }
}
