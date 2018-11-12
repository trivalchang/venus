#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QCursor>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void displayImage(cv::Mat img);
    void startPlay();
    void endPlay();
    void resizeEvent( QResizeEvent *e );

private slots:
    void handleOpenFileBtn();
    void handleOpenCameraBtn();
    void handleSnapshotBtn();
    void handlePlayBtn();
    void updateVideoFrame();
    void resizeDone();
private:
    Ui::MainWindow *ui;
    QTimer *videoTimer;
    QTimer m_resizeTimer;
    QTime m_videoStartTime;
    QTime m_videoElapsedTime;
    bool m_videoPlaying;
    cv::VideoCapture m_videoCap;
    cv::Mat m_currentVFrame;
    bool m_videoPaued;
};

#endif // MAINWINDOW_H
