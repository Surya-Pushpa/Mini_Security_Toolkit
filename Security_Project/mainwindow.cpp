#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"encrption.h"
#include"decrypt.h"
#include"hashing_sender.h"
#include<QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(700,700);



    QPixmap bkgnd("F:/6th Sem/Linux Project/Security_Project/darkbg.jpeg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
       ui->encoding->setStyleSheet("background-color:orange;");
       ui->hashing->setStyleSheet("background-color:orange;");
       ui->steg->setStyleSheet("background-color:orange;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encoding_clicked()
{
    //this->destroy();
    Encrption enc;
    enc.setModal(true);
    enc.exec();

}

void MainWindow::on_hashing_clicked()
{
    hashing_sender hash;
    hash.setModal(true);
    hash.exec();
}


