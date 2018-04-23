#ifndef DECRYPT_H
#define DECRYPT_H

#include <QWidget>

namespace Ui {
class Decrypt;
}

class Decrypt : public QWidget
{
    Q_OBJECT

public:
    explicit Decrypt(QWidget *parent = 0);
    ~Decrypt();

private:
    Ui::Decrypt *ui;
};

#endif // DECRYPT_H
