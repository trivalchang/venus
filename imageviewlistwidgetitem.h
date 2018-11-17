#ifndef IMAGEVIEWLISTWIDGETITEM_H
#define IMAGEVIEWLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QIcon>
#include <QListWidget>
#include <QString>

class ImageViewListWidgetItem:public QListWidgetItem
{
public:
    ImageViewListWidgetItem(const QIcon & icon, const QString & text, int index, QListWidget * parent = nullptr, int type = Type);
    int index() { return m_index; }
private:
    int m_index;
};

#endif // IMAGEVIEWLISTWIDGETITEM_H
