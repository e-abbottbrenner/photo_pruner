#ifndef PRINTHELPERS
#define PRINTHELPERS

#include <iostream>

class QString;
class QJsonObject;

extern ::std::ostream& operator<<(::std::ostream& os, const QString& string);

extern void PrintTo(const QString& string, ::std::ostream* os);\
extern void PrintTo(const QJsonObject& object, ::std::ostream* os);

#endif // PRINTHELPERS

