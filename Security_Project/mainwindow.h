#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <qmath.h>

#include "HexPi.h"
#include "qblowfish.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_encoding_clicked();

    void on_hashing_clicked();

    void on_encoding_2_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
