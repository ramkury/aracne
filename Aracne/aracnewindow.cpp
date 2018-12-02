#include "aracnewindow.h"
#include "ui_aracnewindow.h"

AracneWindow::AracneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AracneWindow)
{
    ui->setupUi(this);
}

AracneWindow::~AracneWindow()
{
    delete ui;
}

void AracneWindow::on_actionSpider_triggered()
{

}

void AracneWindow::on_pushButton_clicked()
{

}
