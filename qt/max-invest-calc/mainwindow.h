
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void btnCalcClicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    int calcMaxInvest(std::vector<int> nums);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
