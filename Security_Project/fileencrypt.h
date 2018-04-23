#ifndef FILEENCRYPT_H
#define FILEENCRYPT_H

#include <QWidget>

namespace Ui {
class FileEncrypt;
}

class FileEncrypt : public QWidget
{
    Q_OBJECT

public:
    explicit FileEncrypt(QWidget *parent = 0);
    ~FileEncrypt();

private slots:
    void on_encodeButton_clicked();

    void on_decodeButton_clicked();

private:
    Ui::FileEncrypt *ui;
};

#endif // FILEENCRYPT_H
