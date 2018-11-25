
#include <QJsonObject>
#include "patternsave.h"

void patternSave::addItem(QString name, patternSave::PATTERN_TYPE type)
{
    patternSave::ITEM item;

    item.m_name = name;
    item.m_type = type;
    m_items.push_back(item);
}

void patternSave::save()
{
    QJsonObject json;
    patternSave::ITEM item;

    while (m_items.isEmpty() == false)
    {
        item = m_items.first();
        m_items.removeFirst();
    }
}
