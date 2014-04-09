
#include <QApplication>
#include <QWidget>
#include <QTextStream>

#include "test.h"
#include "image-box.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ImageBox window;
    window.resize(600, 600);
    window.setWindowTitle("Hello, QT!");
    window.show();

    // output message to stdout
    QTextStream out(stdout);
    out.setCodec("UTF-8");
    out << "The first QT program startup, hello, QT!\n";

    testQfile();
    testQlist();
    testQdir();
    return app.exec();
}
