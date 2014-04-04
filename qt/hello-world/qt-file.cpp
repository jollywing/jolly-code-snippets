
#include <QFile>
#include <QTextStream>

void testQfile()
{
    // output message to file
    QFile file("qt.log");
    if(file.open(QFile::WriteOnly)){
        QTextStream of(&file);
        of.setCodec("UTF-8");
        of << "Hello, QT world!" << endl;
        file.close();
    }

    // read file and output to stdout
    if(file.open(QFile::ReadOnly)){
        QTextStream in_file(&file);
        in_file.setCodec("UTF-8");

        QString line;
        QTextStream out(stdout);
        while(!in_file.atEnd()){
            line = in_file.readLine();
            out << line << endl;
        }
    }
}
