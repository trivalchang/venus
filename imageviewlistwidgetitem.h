#ifndef IMAGEVIEWLISTWIDGETITEM_H
#define IMAGEVIEWLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QIcon>
#include <QListWidget>
#include <QString>
#include <QTime>

class ImageViewListWidgetItem:public QListWidgetItem
{
public:
    ImageViewListWidgetItem(const QIcon & icon, const QString & text, int index, QListWidget * parent = nullptr, int type = Type);
    int index() { return m_index; }
    void setTime(QTime capTime) { m_hour = capTime.hour(); m_second = capTime.minute(); m_second = capTime.second(); }
    int hour() { return m_hour; }
    int minute() { return m_minute; }
    int second() { return m_second; }
private:
    int m_index;
    int m_hour;
    int m_minute;
    int m_second;
};

#endif // IMAGEVIEWLISTWIDGETITEM_H
