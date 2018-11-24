#ifndef PATTERNSAVE_H
#define PATTERNSAVE_H

#include <QString>
#include <QVector>
class patternSave
{
public:
    typedef enum
    {
        PATTERN_TYPE_IMAGE,
        PATTERN_TYPE_OCR_TEXT,
    } PATTERN_TYPE;

    class ITEM
    {
    public:
        PATTERN_TYPE m_type;
        QString m_name;
    };
    patternSave() {}
    void addItem(QString name, PATTERN_TYPE type);
    void save();
private:

    QVector<ITEM> m_items;
};

#endif // PATTERNSAVE_H
