#include "decrypt.h"
#include "ui_decrypt.h"
#include"des.h"
#include <string.h>
#include <stdio.h>
//#include<conio.h>
#include <stdlib.h>
#include<math.h>


Decrypt::Decrypt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Decrypt)
{
    ui->setupUi(this);
    this->setFixedSize(700,700);
    ui->label1->setStyleSheet("QLabel {  color : orange; }");
    ui->label2->setStyleSheet("QLabel {  color : orange; }");

    ui->label5->setStyleSheet("QLabel {  color : orange; }");
    ui->label4->setStyleSheet("QLabel {  color : orange; }");
    ui->radioButton->setStyleSheet("QRadioButton {  color : orange; }");
    ui->radioButton_3->setStyleSheet("QRadioButton {  color : orange; }");
    ui->radioButton_4->setStyleSheet("QRadioButton {  color : orange; }");
    ui->radioButton_5->setStyleSheet("QRadioButton {  color : orange; }");
    ui->radioButton_6->setStyleSheet("QRadioButton {  color : orange; }");


    QPixmap bkgnd("F:/6th Sem/Linux Project/Security_Project/darkbg.jpeg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
}

Decrypt::~Decrypt()
{
    delete ui;
}
