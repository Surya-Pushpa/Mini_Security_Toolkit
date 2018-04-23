#-------------------------------------------------
#
# Project created by QtCreator 2018-02-18T02:56:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Security_Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    encrption.cpp \
    des.cpp \
    hashing_sender.cpp \
    sha_1.cpp \
    md5.cpp \
    decrypt.cpp \
    fileencrypt.cpp \
    qblowfish.cpp

HEADERS  += mainwindow.h \
    encrption.h \
    des.h \
    hashing_sender.h \
    md5.h \
    decrypt.h \
    fileencrypt.h \
    qblowfish.h \
    HexPi.h

FORMS    += mainwindow.ui \
    encrption.ui \
    hashing_sender.ui \
    decrypt.ui \
    fileencrypt.ui
