#include "imageviewlistwidgetitem.h"

ImageViewListWidgetItem::ImageViewListWidgetItem(const QIcon & icon, const QString & text, int index, QListWidget * parent, int type)
    :QListWidgetItem(icon, text, parent, type)
    ,m_index(index)
{

}
