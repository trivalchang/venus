#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QCursor>
#include <QVector>
#include <QListWidgetItem>
#include <QMutex>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <imagedisplaylabel.h>
#include <patternsave.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startPlay(QString fname);
    void endPlay();
    void resizeEvent( QResizeEvent *e );

private slots:
    void handleOpenFileBtn();
    void handleOpenCameraBtn();
    void handleSnapshotBtn();
    void handlePlayBtn();
    void updateVideoFrame();
    void resizeDone();
    void onSnapshotViewItemPressed(QListWidgetItem *item);
    void handleSaveBtn();
private:
    void relocateWidget(QWidget *widget, QSizeF ratio);
    Ui::MainWindow *ui;
    QTimer *videoTimer;
    QTimer m_resizeTimer;
    QTime m_videoStartTime;
    QTime m_videoElapsedTime;
    bool m_videoPlaying;
    cv::VideoCapture m_videoCap;
    cv::Mat m_currentVFrame;
    bool m_videoPaued;
    QString m_filePlaying;
    int m_videoElapsedInMs;
    QVector<cv::Mat> m_snapshotFrames;
    QString m_snapshotsTabText;
    patternSave m_patternSave;
};

#endif // MAINWINDOW_H
