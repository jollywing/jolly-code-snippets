
#include <QApplication>
#include <QWidget>
#include <QTextStream>

#include "test.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(250, 150);
    window.setWindowTitle("Hello, QT!");
    window.show();

    // output message to stdout
    QTextStream out(stdout);
    out.setCodec("UTF-8");
    out << "The first QT program startup, hello, QT!\n";

    testQfile();
    testQlist();
    return app.exec();
}
