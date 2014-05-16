#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnInsertBook()
{

    if(ui->mainPanel->tabPosition() == QTabWidget::North)
        ui->mainPanel->setTabPosition(QTabWidget::South);
    else
        ui->mainPanel->setTabPosition(QTabWidget::North);
    ui->mainPanel->setTabEnabled(1, true);
}

void MainWindow::OnSaveBooks()
{
    ui->statusBar->showMessage("Book Database Saved.");
    ui->mainPanel->setStyleSheet("QLineEdit{color:red; background:cyan}");
}
