#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QResizeEvent>
#include <imageviewlistwidgetitem.h>
#include <baseapi.h>

#include <QtDebug>


using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_videoPlaying(false),
    m_videoPaued(false)
{
    ui->setupUi(this);

    ui->ImageDisplay->enableDrawROI(false);
    ui->ImageEdit->enableDrawROI(false);

    ui->typeComboBox->addItem("Words");
    ui->typeComboBox->addItem("Image");

    videoTimer = new QTimer(this);
    connect(ui->OpenCameraBtn, SIGNAL (released()),this, SLOT (handleOpenCameraBtn()));
    connect(ui->OpenFileBtn, SIGNAL (released()),this, SLOT (handleOpenFileBtn()));
    connect(ui->PlayBtn, SIGNAL (released()),this, SLOT (handlePlayBtn()));
    connect(ui->SnapshotBtn, SIGNAL (released()),this, SLOT (handleSnapshotBtn()));
    connect(ui->saveBtn, SIGNAL (released()),this, SLOT (handleSaveBtn()));

    connect(videoTimer, SIGNAL(timeout()),this, SLOT(updateVideoFrame()));
    QTimer::singleShot(500, this, SLOT(showMaximized()));
    //m_resizeTimer.setSingleShot( true );
    connect( &m_resizeTimer, SIGNAL(timeout()), SLOT(resizeDone()) );

    setWindowTitle(tr("Window Flags"));
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

    m_snapshotsTabText = ui->tabWidget->tabText(1);
    ui->SnapshotList0->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->SnapshotList1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->SnapshotList1, SIGNAL(itemPressed(QListWidgetItem*)),this, SLOT(onSnapshotViewItemPressed(QListWidgetItem*)));
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
    int w, h, oldw, oldh;
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

    wratio = static_cast<qreal>(w)/static_cast<qreal>(oldw);
    hratio = static_cast<qreal>(h)/static_cast<qreal>(oldh);


    m_resizeTimer.start( 500 );
    QMainWindow::resizeEvent(e);
    relocateWidget(ui->tabWidget, QSizeF(wratio, hratio));
    relocateWidget(ui->ImageDisplay, QSizeF(wratio, hratio));
    relocateWidget(ui->SnapshotList0, QSizeF(wratio, hratio));
    relocateWidget(ui->videoElapsed, QSizeF(wratio, hratio));

    relocateWidget(ui->ImageEdit, QSizeF(wratio, hratio));
    relocateWidget(ui->SnapshotList1, QSizeF(wratio, hratio));
    relocateWidget(ui->idLabel, QSizeF(wratio, hratio));
    relocateWidget(ui->idEdit, QSizeF(wratio, hratio));
    relocateWidget(ui->typeLabel, QSizeF(wratio, hratio));
    relocateWidget(ui->typeComboBox, QSizeF(wratio, hratio));
    relocateWidget(ui->saveBtn, QSizeF(wratio, hratio));
    relocateWidget(ui->OcrImageDisplay, QSizeF(wratio, hratio));
    relocateWidget(ui->OcrResultEdit, QSizeF(wratio, hratio));
    relocateWidget(ui->OcrResultLabel, QSizeF(wratio, hratio));
}

void MainWindow::resizeDone()
{
}

void MainWindow::handleSnapshotBtn()
{
    m_snapshotFrames.push_back(m_currentVFrame.clone());
    QString title = m_snapshotsTabText + "(" + QString::number(m_snapshotFrames.size()) + ")";
    ui->tabWidget->setTabText(1, title);

    QIcon icon;
    QPixmap pixMap;


    QImage imdisplay(static_cast<uchar*>(m_currentVFrame.data),
                     m_currentVFrame.cols,
                     m_currentVFrame.rows,
                     static_cast<int>(m_currentVFrame.step),
                     QImage::Format_RGB888);
    icon.addPixmap(QPixmap::fromImage(imdisplay));
    ImageViewListWidgetItem *item = new ImageViewListWidgetItem(icon, nullptr, m_snapshotFrames.size()-1);
    ImageViewListWidgetItem *item1 = new ImageViewListWidgetItem(icon, nullptr, m_snapshotFrames.size()-1);

    item->setTime(m_videoElapsedTime);
    item1->setTime(m_videoElapsedTime);

    if (m_videoElapsedTime.minute() >= 1)
    {
        printf("m_videoElapsedTime = %d\n", m_videoElapsedTime.minute());
    }

    QSize iconSize;

    iconSize.setWidth(ui->SnapshotList0->maximumViewportSize().width());

    ui->SnapshotList0->setMinimumWidth(iconSize.width());
    iconSize.setWidth(ui->SnapshotList0->width()-ui->SnapshotList0->spacing()*2);
    iconSize.setHeight(static_cast<int>(static_cast<qreal>(ui->SnapshotList0->height()) * \
                        (static_cast<qreal>(m_currentVFrame.cols)/static_cast<qreal>(m_currentVFrame.rows))));
    ui->SnapshotList0->setIconSize(iconSize);

    ui->SnapshotList0->addItem(item);

    ui->SnapshotList1->setIconSize(iconSize);

    ui->SnapshotList1->addItem(item1);

    ui->ImageEdit->enableDrawROI(true);

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
    cv::cvtColor(m_currentVFrame,m_currentVFrame,COLOR_BGR2RGB);
    if (!m_currentVFrame.empty())
    {
        ui->ImageDisplay->displayImage(m_currentVFrame);
        m_videoElapsedTime = m_videoElapsedTime.addMSecs(m_videoStartTime.elapsed() - m_videoElapsedInMs);
        m_videoElapsedInMs = m_videoStartTime.elapsed();
        ui->videoElapsed->setText(m_videoElapsedTime.toString("hh:mm:ss"));
        ui->videoElapsed->repaint();
    }
}

void MainWindow::onSnapshotViewItemPressed(QListWidgetItem *item)
{
    ImageViewListWidgetItem *item1 = dynamic_cast<ImageViewListWidgetItem *>(item);
    if (item1 == nullptr)
    {
        printf("unable to cast\n");
        return;
    }
    ui->ImageEdit->displayImage(m_snapshotFrames[item1->index()]);
    ui->idEdit->setText(QString::number(item1->hour()) + "_" + QString::number(item1->minute()) + "_" + QString::number(item1->second()));
}

void MainWindow::handleSaveBtn()
{
    QRect roi;

    ui->ImageEdit->getROI(roi);
    cv::Mat gray = m_snapshotFrames[0];
    float ratioH, ratioW;

    ratioW = float(gray.cols)/float(ui->ImageEdit->width());
    ratioH = float(gray.rows)/float(ui->ImageEdit->height());
    cv::Rect rect(int(float(roi.x()) * ratioW),
               int(float(roi.y()) * ratioH),
               int(float(roi.width()) * ratioW),
               int(float(roi.height()) * ratioH));

    gray = gray(rect) ;

#if 1
    cv::cvtColor(gray, gray, COLOR_RGB2GRAY);
    tesseract::TessBaseAPI tess;
    if (tess.Init(TESSERACT_DATA, "eng", tesseract::OEM_DEFAULT) == -1)
    {
        printf("Unable to init\n");
        qInfo() << "Unable to init\n";
        ui->OcrResultEdit->setText("ERROR");
        return;
    }
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage((uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols);

    //printf("I am here\n");
    // Get the text
    char* out = tess.GetUTF8Text();

    printf("OCR: %s\n", out);

    ui->OcrImageDisplay->displayImage(gray);
    ui->OcrResultEdit->setText(out);
    ui->ImageEdit->enableDrawROI(true);
    m_patternSave.addItem(out, patternSave::PATTERN_TYPE_OCR_TEXT);
    m_patternSave.save();
#endif
}
