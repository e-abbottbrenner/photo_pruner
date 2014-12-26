#include "PrintHelpers.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

extern void PrintTo(const QString &string, std::ostream *os)
{
    *os << string.toStdString();
}

extern void PrintTo(const QJsonObject &object, std::ostream *os)
{
    QJsonDocument document;
    document.setObject(object);
    *os << document.toJson().toStdString();
}
