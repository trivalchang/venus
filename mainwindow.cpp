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
    connect(videoTimer, SIGNAL(timeout()),this, SLOT(updateVideoFrame()));
    //QTimer::singleShot(500, this, SLOT(showFullScreen()));
    //m_resizeTimer.setSingleShot( true );
    //connect( &m_resizeTimer, SIGNAL(timeout()), SLOT(resizeDone()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startPlay()
{
    videoTimer->start(100);
    m_videoPlaying = true;
    m_videoCap.open(0);
    if (!m_videoCap.isOpened())
    {
        printf("Unable to open video\n");
    }

    ui->OpenCameraBtn->setText("Stop");
    ui->OpenCameraBtn->repaint();
    m_videoStartTime.start();
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
        startPlay();
    }
    else
    {
        endPlay();
    }
}

void MainWindow::handleOpenFileBtn()
{
    if (m_videoPlaying == false)
    {
        startPlay();
    }
    else
    {
        endPlay();
    }
}

void MainWindow::resizeEvent( QResizeEvent *e )
{
    int w, h;

    w = e->size().width();
    h = e->size().height();

    m_resizeTimer.start( 500 );
    QMainWindow::resizeEvent(e);
    printf("Resize\n");
    printf("orig window size %d x %d\n", size().width(), size().height());
    ui->tabWidget->resize(w-100, h-100);
    ui->ImageDisplay->resize(w-100, h-100);
}

void MainWindow::resizeDone()
{
    int w, h;

    w = size().width();
    h = size().height();
    printf("new window size %d x %d\n", size().width(), size().height());
}

void MainWindow::handleSnapshotBtn()
{
}

void MainWindow::handlePlayBtn()
{
    m_videoPaued = !m_videoPaued;
}

void MainWindow::updateVideoFrame()
{
    if (m_videoPaued)
    {
        return;
    }
    m_videoCap >> m_currentVFrame;

    printf("updateVideoFrame\n");
    if (!m_currentVFrame.empty())
    {
        displayImage(m_currentVFrame);
    }

    static int elapsed = 0;

    m_videoElapsedTime = m_videoElapsedTime.addMSecs(m_videoStartTime.elapsed() - elapsed);
    elapsed = m_videoStartTime.elapsed();
    ui->videoElapsed->setText(m_videoElapsedTime.toString("hh:mm:ss.zzz"));
    ui->videoElapsed->repaint();
}

void MainWindow::displayImage(cv::Mat img)
{
    cv::resize(img, img, Size(ui->ImageDisplay->size().width(), ui->ImageDisplay->size().height()), 0, 0, INTER_LINEAR);
    cv::cvtColor(img,img,COLOR_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    ui->ImageDisplay->setPixmap(QPixmap::fromImage(imdisplay));
    ui->ImageDisplay->repaint();
}
