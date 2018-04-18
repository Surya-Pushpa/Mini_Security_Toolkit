#ifndef HASHING_H
#define HASHING_H

#include <QDialog>

namespace Ui {
class Hashing;
}

class Hashing : public QDialog
{
    Q_OBJECT

public:
    explicit Hashing(QWidget *parent = 0);
    ~Hashing();

private:
    Ui::Hashing *ui;
};

#endif // HASHING_H
