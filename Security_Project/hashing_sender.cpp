#include "hashing_sender.h"
#include "ui_hashing_sender.h"
#include "sha_1.cpp"
#include "md5.h"
#include "md5.cpp"
#include<QFileDialog>
#include<QMessageBox>
QString filename;
hashing_sender::hashing_sender(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hashing_sender)
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

}

hashing_sender::~hashing_sender()
{
    delete ui;
}

void hashing_sender::on_sender_clicked()
{
    QString str = ui->comboBox_2->currentText();
    QString qis = ui->textEdit->toPlainText();

    if(str == "SHA 1"){

        QByteArray ba = qis.toLocal8Bit();
        unsigned char *res = (unsigned char *)strdup(ba.constData());

        string str = SHA1((unsigned char *)res);

        QString qstr = QString::fromStdString(str);

        ui->textBrowser->setText(qstr);
    }
    if(str == "MD5"){

        std::string str = md5(qis.toStdString());
        QString qstr = QString::fromStdString(str);

        ui->textBrowser->setText(qstr);
    }
}

void hashing_sender::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All file (*.*);;Text File (*.txt)"
                );
    QMessageBox::information(this,tr("File Name"),filename);
}
