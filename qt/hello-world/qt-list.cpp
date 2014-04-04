
#include <QList>
#include <QTextStream>

void testQlist()
{
    // QT list
    QList<QString> list;
    list << "hello";
    list << "QT" << "World!";
    list.append("Pig, Dog");

    QTextStream out(stdout);
    short i;
    for(i = 0; i < list.length(); i ++){
        out << list.at(i) << endl;
    }
}
