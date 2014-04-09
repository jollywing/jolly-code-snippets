
#include <QTextStream>
#include <QDir>

void testQdir()
{
    QTextStream out(stdout);
    out << "Test QDir begin ..." << endl;
    QString home = QDir::homePath();
    out << "$Home: " << home << endl;

    QDir dir("~");
    QStringList filters;
    filters << "*.pdf" << "*.ps";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();
    int i;
    if(list.size() <= 0)
        out << "No pdf file." << endl;
    else {
        out << "PDF files:" << endl;
        for(i = 0; i < list.size(); i ++) {
            QFileInfo info = list.at(i);
            out << QString("%1").arg(info.fileName()) << endl;
        }
    }
}
