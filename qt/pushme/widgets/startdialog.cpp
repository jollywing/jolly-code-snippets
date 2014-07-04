#include "startdialog.h"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::on_exitButton_clicked()
{
    result = CANCEL;
    this->hide();
    exit(0);
}

void StartDialog::on_startButton_clicked()
{
    result = OK;
    this->hide();
}

int StartDialog::getResult()
{
    return result;
}
