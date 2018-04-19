#ifndef HASHING_RECEIVER_H
#define HASHING_RECEIVER_H

#include <QDialog>

namespace Ui {
class Hashing_receiver;
}

class Hashing_receiver : public QDialog
{
    Q_OBJECT

public:
    explicit Hashing_receiver(QWidget *parent = 0);
    ~Hashing_receiver();

private slots:
    void on_pushButton_clicked();

    void on_check_clicked();

private:
    Ui::Hashing_receiver *ui;
};

#endif // HASHING_RECEIVER_H
