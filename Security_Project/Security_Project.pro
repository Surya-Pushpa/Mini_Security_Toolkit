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
    sha256.cpp \
    sha512.cpp \
    sha384.cpp \
    sha224.cpp \
    hashing_receiver.cpp \
    hashing_algorithms.cpp

HEADERS  += mainwindow.h \
    encrption.h \
    des.h \
    hashing_sender.h \
    md5.h \
    sha256.h \
    sha512.h \
    sha384.h \
    sha224.h \
    hashing_receiver.h \
    hashing_algorithms.h

FORMS    += mainwindow.ui \
    encrption.ui \
    hashing_sender.ui \
    hashing_receiver.ui
