#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_videoPlaying(false)
{
    ui->setupUi(this);
    connect(ui->StartButton, SIGNAL (released()),this, SLOT (handleButton()));
    videoTimer = new QTimer(this);
    connect(videoTimer, SIGNAL(timeout()),this, SLOT(updateVideoFrame()));
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

    ui->StartButton->setText("Stop");
    ui->StartButton->repaint();
    m_videoStartTime.start();
    m_videoElapsedTime.setHMS(0, 0, 0);
}

void MainWindow::endPlay()
{
    videoTimer->stop();
    m_videoPlaying = false;
    m_videoCap.release();
    ui->StartButton->setText("Star");
    ui->StartButton->repaint();
}

void MainWindow::handleButton()
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


void MainWindow::updateVideoFrame()
{

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
    cv::cvtColor(img,img,CV_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    ui->ImageDisplay->setPixmap(QPixmap::fromImage(imdisplay));
    ui->ImageDisplay->repaint();
}
