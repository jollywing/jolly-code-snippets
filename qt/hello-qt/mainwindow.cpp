#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressLabel->setText(QString::number(ui->progressBar->value()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    QObject::connect(ui->leftButton, SIGNAL(clicked()), this, SLOT(decreaseProgress()));
    QObject::connect(ui->rightButton, SIGNAL(clicked()), this, SLOT(increaseProgress()));
}

void MainWindow::decreaseProgress()
{
    int oldValue = ui->progressBar->value();
    int newValue = oldValue - ui->progressBar->singleStep();
    if (newValue < ui->progressBar->minimum())
        newValue = ui->progressBar->minimum();
    ui->progressBar->setValue(newValue);
    ui->progressLabel->setText(QString::number(ui->progressBar->value()));
}

void MainWindow::increaseProgress()
{
    int oldValue = ui->progressBar->value();
    int newValue = oldValue + ui->progressBar->singleStep();
    if (newValue > ui->progressBar->maximum())
        newValue = ui->progressBar->maximum();
    ui->progressBar->setValue(newValue);
    ui->progressLabel->setText(QString::number(ui->progressBar->value()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
