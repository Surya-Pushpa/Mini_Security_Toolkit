#ifndef ENCRPTION_H
#define ENCRPTION_H

#include <QDialog>

namespace Ui {
class Encrption;
}

class Encrption : public QDialog
{
    Q_OBJECT

public:
    explicit Encrption(QWidget *parent = 0);
    ~Encrption();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_clicked();

    void on_radioButton_6_clicked();

private:
    Ui::Encrption *ui;
};

#endif // ENCRPTION_H
