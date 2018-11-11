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

private slots:
    void handleButton();
    void updateVideoFrame();
private:
    Ui::MainWindow *ui;
    QTimer *videoTimer;
    QTime m_videoStartTime;
    QTime m_videoElapsedTime;
    bool m_videoPlaying;
    cv::VideoCapture m_videoCap;
};

#endif // MAINWINDOW_H
