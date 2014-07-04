#include "pushme.h"
#include "startdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialog d;
    d.show();
    if(d.getResult() == StartDialog::OK){
        Dialog w;
        w.show();
    }

    return a.exec();
}
