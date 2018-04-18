#ifndef HASHING_SENDER_H
#define HASHING_SENDER_H

#include <QDialog>

namespace Ui {
class hashing_sender;
}

class hashing_sender : public QDialog
{
    Q_OBJECT

public:
    explicit hashing_sender(QWidget *parent = 0);
    ~hashing_sender();

private slots:
    void on_sender_clicked();

    void on_pushButton_clicked();

private:
    Ui::hashing_sender *ui;
};

#endif // HASHING_SENDER_H
