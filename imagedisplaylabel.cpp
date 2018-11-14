
#include "imagedisplaylabel.h"
#include <QtGlobal>

ImageDisplayLabel::ImageDisplayLabel(QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent,f)
    ,m_bDrawROI(false)
    ,m_ROIStart{-1,-1}
    ,m_ROIEnd{-1,-1}
{
    setMouseTracking(true);
}

void ImageDisplayLabel::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPoint invalid(-1, -1);
    paint.setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap));
    paint.drawPixmap(QPoint(0, 0), QPixmap::fromImage(m_imgToDraw));
    //paint.drawLine(0, 0, 200, 200);
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
    m_ROIEnd = event->pos();
    repaint();
}

void ImageDisplayLabel::mousePressEvent(QMouseEvent *event)
{
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
}

void ImageDisplayLabel::displayImage(QImage imgToDraw)
{
    m_imgToDraw = imgToDraw.copy();
    repaint();
}
