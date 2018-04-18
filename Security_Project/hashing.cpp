#include "hashing.h"
#include "ui_hashing.h"

Hashing::Hashing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hashing)
{
    ui->setupUi(this);
    QPixmap bkgnd("F:/6th Sem/Linux Project/Security_Project/darkbg.jpeg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
}

Hashing::~Hashing()
{
    delete ui;
}
