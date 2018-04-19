#include "iostream"
#include "hashing_algorithms.h"

#include "md5.h"
#include "md5.cpp"
#include "sha224.h"
#include "sha224.cpp"
#include "sha_1.cpp"
#include "sha256.h"
#include "sha256.cpp"
#include "sha384.h"
#include "sha384.cpp"
#include "sha512.h"
#include "sha512.cpp"

QString calculateHashValue(QString algostr , QString qis){

    QString qstr;
    if(algostr == "SHA 1"){

        QByteArray ba = qis.toLocal8Bit();
        unsigned char *res = (unsigned char *)strdup(ba.constData());

        string str = SHA1((unsigned char *)res);

        qstr = QString::fromStdString(str);

    }
    if(algostr == "MD5"){

        std::string str = md5(qis.toStdString());
        qstr = QString::fromStdString(str);

    }
    if(algostr == "SHA 256"){

        std::string str = sha256(qis.toStdString());
        qstr = QString::fromStdString(str);

    }
    if(algostr == "SHA 512"){

        std::string str = sha512(qis.toStdString());
        qstr = QString::fromStdString(str);

    }
    if(algostr == "SHA 384"){

        std::string str = sha384(qis.toStdString());
        qstr = QString::fromStdString(str);

    }
    if(algostr == "SHA 224"){

        std::string str = sha224(qis.toStdString());
        qstr = QString::fromStdString(str);

    }
    return qstr;
}

