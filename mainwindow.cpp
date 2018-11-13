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

void MainWindow::resizeEvent( QResizeEvent *e )
{
    int w, h;

    w = e->size().width();
    h = e->size().height();

    m_resizeTimer.start( 500 );
    QMainWindow::resizeEvent(e);
    ui->tabWidget->resize(w*0.98, h*0.80);
    ui->ImageDisplay->resize(w*0.98, h*0.70);
}

void MainWindow::resizeDone()
{
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
    int newW, newH;
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
    ui->ImageDisplay->setPixmap(QPixmap::fromImage(imdisplay));
    ui->ImageDisplay->repaint();
}
