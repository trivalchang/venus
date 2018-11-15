#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QResizeEvent>

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_videoPlaying(false),
    m_videoPaued(false)
{
    ui->setupUi(this);
    videoTimer = new QTimer(this);
    connect(ui->OpenCameraBtn, SIGNAL (released()),this, SLOT (handleOpenCameraBtn()));
    connect(ui->OpenFileBtn, SIGNAL (released()),this, SLOT (handleOpenFileBtn()));
    connect(ui->PlayBtn, SIGNAL (released()),this, SLOT (handlePlayBtn()));
    connect(ui->SnapshotBtn, SIGNAL (released()),this, SLOT (handleSnapshotBtn()));

    connect(videoTimer, SIGNAL(timeout()),this, SLOT(updateVideoFrame()));
    QTimer::singleShot(500, this, SLOT(showMaximized()));
    //m_resizeTimer.setSingleShot( true );
    connect( &m_resizeTimer, SIGNAL(timeout()), SLOT(resizeDone()) );

    setWindowTitle(tr("Window Flags"));
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

    m_snapshotsTabText = ui->tabWidget->tabText(1);
    ui->SnapshotList0->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startPlay(QString fname)
{
    videoTimer->start(10);
    m_videoPlaying = true;
    if (fname == "")
    {
        m_videoCap.open(0);
    }
    else
    {
        m_videoCap.open(fname.toStdString());
    }

    if (!m_videoCap.isOpened())
    {
        printf("Unable to open video\n");
    }

    ui->OpenCameraBtn->setText("Stop");
    ui->OpenCameraBtn->repaint();
    m_videoStartTime.start();
    m_videoElapsedInMs = 0;
    m_videoElapsedTime.setHMS(0, 0, 0);
}

void MainWindow::endPlay()
{
    videoTimer->stop();
    m_videoPlaying = false;

    m_videoCap.release();
    ui->OpenCameraBtn->setText("Star");
    ui->OpenCameraBtn->repaint();
}

void MainWindow::handleOpenCameraBtn()
{
    if (m_videoPlaying == false)
    {
        startPlay("");
    }
    else
    {
        endPlay();
    }
}

void MainWindow::handleOpenFileBtn()
{
    m_filePlaying = QFileDialog::getOpenFileName(this,tr("Open video files"),".",
                                             "mov (*.mov);;AVI (*.avi);;MP4 (*.MP4)");
    startPlay(m_filePlaying);
}

void MainWindow::relocateWidget(QWidget *widget, QSizeF ratio)
{
    int neww, newh;
    int newx, newy;

    neww = (int)((qreal)widget->size().width() * ratio.width());
    newh = (int)((qreal)widget->size().height() * ratio.height());
    widget->resize(neww, newh);
    newx = (int)((qreal)widget->pos().x() * ratio.width());
    newy = (int)((qreal)widget->pos().y() * ratio.height());
    widget->move(newx, newy);
}

void MainWindow::resizeEvent( QResizeEvent *e )
{
    int w, h, oldw, oldh, neww, newh;
    qreal wratio, hratio;

    if ((e->size().isValid() == false) ||
            (e->oldSize().isValid() == false))
    {
        return;
    }

    w = e->size().width();
    h = e->size().height();
    oldw = e->oldSize().width();
    oldh = e->oldSize().height();

    wratio = (qreal)w/(qreal)oldw;
    hratio = (qreal)h/(qreal)oldh;


    m_resizeTimer.start( 500 );
    QMainWindow::resizeEvent(e);
    relocateWidget(ui->tabWidget, QSizeF(wratio, hratio));
    relocateWidget(ui->ImageDisplay, QSizeF(wratio, hratio));
    relocateWidget(ui->SnapshotList0, QSizeF(wratio, hratio));
    relocateWidget(ui->videoElapsed, QSizeF(wratio, hratio));

}

void MainWindow::resizeDone()
{
}

void MainWindow::handleSnapshotBtn()
{
    m_snapshotFrames.push_back(m_currentVFrame);
    QString title = m_snapshotsTabText + "(" + QString::number(m_snapshotFrames.size()) + ")";
    ui->tabWidget->setTabText(1, title);

    QIcon icon;
    QPixmap pixMap;


    QImage imdisplay((uchar*)m_currentVFrame.data, m_currentVFrame.cols, m_currentVFrame.rows, m_currentVFrame.step, QImage::Format_RGB888);
    icon.addPixmap(QPixmap::fromImage(imdisplay));
    QListWidgetItem *item = new QListWidgetItem(icon,NULL);

    QSize iconSize;
    //ui->SnapshotList0->setSpacing(0);
    //iconSize.setWidth(ui->SnapshotList0->width()-ui->SnapshotList0->spacing()*2);
    iconSize.setWidth(ui->SnapshotList0->maximumViewportSize().width());
    printf("maximumViewportSize = %d\n", ui->SnapshotList0->maximumViewportSize().width());
    printf("size = %d\n", ui->SnapshotList0->size().width());

    ui->SnapshotList0->setMinimumWidth(iconSize.width());
    iconSize.setWidth(ui->SnapshotList0->width()-ui->SnapshotList0->spacing()*2);
    iconSize.setHeight((qreal)ui->SnapshotList0->height() * ((qreal)m_currentVFrame.cols/(qreal)m_currentVFrame.rows));
    ui->SnapshotList0->setIconSize(iconSize);

    ui->SnapshotList0->addItem(item);
}

void MainWindow::handlePlayBtn()
{
    m_videoPaued = !m_videoPaued;
    if (m_videoPaued == false)
    {
        m_videoStartTime.restart();
        m_videoElapsedInMs = 0;
    }
}

void MainWindow::updateVideoFrame()
{
    if (m_videoPaued)
    {
        return;
    }
    m_videoCap >> m_currentVFrame;
    if (!m_currentVFrame.empty())
    {
        displayImage(m_currentVFrame);
        m_videoElapsedTime = m_videoElapsedTime.addMSecs(m_videoStartTime.elapsed() - m_videoElapsedInMs);
        m_videoElapsedInMs = m_videoStartTime.elapsed();
        ui->videoElapsed->setText(m_videoElapsedTime.toString("hh:mm:ss"));
        ui->videoElapsed->repaint();
    }
}

void MainWindow::displayImage(cv::Mat img)
{
    int newW = 0, newH = 0;
    float imgRatio, displayRatio;

    imgRatio = float(img.cols)/float(img.rows);
    displayRatio = float(ui->ImageDisplay->size().width())/float(ui->ImageDisplay->size().height());
    if (imgRatio >= displayRatio)    // image ratio is wider than display widget
    {
        newW = ui->ImageDisplay->size().width();
        newH = int(float(img.rows) * float(newW)/float(img.cols));
    }
    else if (imgRatio < displayRatio)
    {
        newH = ui->ImageDisplay->size().height();
        newW = int(float(img.cols) * float(newH)/float(img.rows));
    }

    if ((newW != ui->ImageDisplay->size().width()) ||
            (newH != ui->ImageDisplay->size().height()))
    {
        ui->ImageDisplay->resize(newW, newH);
    }

    cv::resize(img, img, Size(newW, newH), 0, 0, INTER_LINEAR);
    cv::cvtColor(img,img,COLOR_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    ui->ImageDisplay->displayImage(imdisplay);
}
