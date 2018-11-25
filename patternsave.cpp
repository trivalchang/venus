
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
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

    QJsonArray jsonItemArray;
    patternSave::ITEM item;

    json.insert("Hello", "I'm here");

    while (m_items.isEmpty() == false)
    {
        QJsonObject jsonItem;
        item = m_items.first();
        jsonItem.insert("Name", item.m_name);
        jsonItem.insert("Type", item.m_type);
        jsonItemArray.push_back(jsonItem);
        m_items.removeFirst();
    }

    json.insert("Pattern", jsonItemArray);
    QJsonDocument jsonDoc(json);

    QFile jsonFile("Pattern.json");
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDoc.toJson());
    jsonFile.close();
}
