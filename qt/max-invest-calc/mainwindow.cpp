#include <QMessageBox>
#include <vector>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btnCalc, SIGNAL(clicked()), this, SLOT(btnCalcClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::btnCalcClicked()
{
    QString invests(ui->textInvests->document()->toPlainText());
    if (!invests.length()) {
        QMessageBox::information(this, "Information", "No data to calculate!");
        return;
    }

    std::vector<int> investNums;
    QStringList intList = invests.split("\n");
    for(QStringList::iterator it = intList.begin(); it != intList.end(); ++it) {
        // QMessageBox::information(this, "Information", *it);
        investNums.push_back(QString(*it).toInt());
    }

    QString result = QString::asprintf("<p style='color:red; font-size:20px'><strong>%d</strong></p>",calcMaxInvest(investNums));
    ui->textResult->setHtml(result);
}

int MainWindow::calcMaxInvest(std::vector<int> nums)
{
    std::vector<int> tmp;
    std::vector<int>::iterator it;
    int sum = 0;
    bool sumRaise = true;
    for(it = nums.begin(); it != nums.end(); ++it) {
        if (*it < 0 && sumRaise) {
            tmp.push_back(sum);
            sumRaise = false;
        }
        if (*it > 0 && !sumRaise)
            sumRaise = true;
        sum += *it;
    }
    tmp.push_back(sum);
    for(it = tmp.begin(); it != tmp.end(); it++)
        std::cout << *it << std::endl;
    std::cout << "=================" << std::endl;

    auto max_it = std::max_element(std::begin(tmp), std::end(tmp));
    return int(*max_it);
}
