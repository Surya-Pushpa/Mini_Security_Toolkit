#include "hashing_receiver.h"
#include "ui_hashing_receiver.h"

#include "hashing_algorithms.h"

#include<QFileDialog>
#include<QMessageBox>
QString filenamer;

Hashing_receiver::Hashing_receiver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hashing_receiver)
{
    ui->setupUi(this);
    QPixmap bkgnd("black");
            bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Background, bkgnd);
            this->setPalette(palette);

        ui->title_hashingsender->setStyleSheet("QLabel {  color : orange; }");
        ui->lineone->setStyleSheet("QLineEdit { background: orange; border: orange }");
        ui->label->setStyleSheet("QLabel { color : orange; }");
        ui->label_2->setStyleSheet("QLabel { color : orange; }");
        ui->label_3->setStyleSheet("QLabel { color : orange; }");
        ui->label_4->setStyleSheet("QLabel { color : orange; }");

}

Hashing_receiver::~Hashing_receiver()
{
    delete ui;
}

void Hashing_receiver::on_pushButton_clicked()
{
    filenamer = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All file (*.*);;Text File (*.txt)"
                );
    QMessageBox::information(this,tr("File Name"),filenamer);
}

void Hashing_receiver::on_check_clicked()
{
    QString qhashvalue = ui->textEdit_2->toPlainText();
    QString algostr = ui->comboBox_2->currentText();
    QString qis = ui->textEdit->toPlainText();
    QString qstr = calculateHashValue(algostr,qis);

    if(qhashvalue == qstr){
        ui->textBrowser->setText("\nMatched!!");
    }
    else{
        ui->textBrowser->setText("\nNot Matched!!");
    }

}
