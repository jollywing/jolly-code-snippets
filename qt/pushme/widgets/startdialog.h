#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

    const static int OK = 1;
    const static int CANCEL = 2;
    int getResult();

private slots:
    void on_exitButton_clicked();

    void on_startButton_clicked();

private:
    Ui::StartDialog *ui;
    int result;
};

#endif // STARTDIALOG_H
