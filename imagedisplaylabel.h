#ifndef IMAGEDISPLAYLABEL_H
#define IMAGEDISPLAYLABEL_H

#include <QLabel>
class ImageDisplayLabel:public QLabel
{
public:
    ImageDisplayLabel(QWidget *parent = NULL, Qt::WindowFlags f=0)
        :QLabel(parent,f)
        {}
};

#endif // IMAGEDISPLAYLABEL_H