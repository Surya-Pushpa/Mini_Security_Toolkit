#include "fileencrypt.h"
#include "ui_fileencrypt.h"


#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <iostream>


FileEncrypt::FileEncrypt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileEncrypt)
{
    ui->setupUi(this);
    this->setFixedSize(700,700);



    QPixmap bkgnd("F:/6th Sem/Linux Project/Security_Project/darkbg.jpeg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

    ui->encodeButton->setStyleSheet("background-color:orange;");

    ui->decodeButton->setStyleSheet("background-color:orange;");
ui->keyLabel->setStyleSheet("QLabel {  color : orange; }");
}

FileEncrypt::~FileEncrypt()
{
    delete ui;
}

void FileEncrypt::on_encodeButton_clicked()
{
    if (ui->keyLineEdit->text().isEmpty()) {
        QMessageBox errorBox;
        errorBox.setText("You must enter a key for encryption.");
        errorBox.setInformativeText("It is best if you pick a long (32 characters or more) key.");
        errorBox.exec();
        // We can't continue.
        return;
    }

    // Select a file - any file that exists
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QString filename = dialog.getOpenFileName();

    // Check that we can open the file
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox errorBox;
        errorBox.setText("The file cannot be read.");
        errorBox.setInformativeText("There may be a permissions problem; ensure that you have the right to open the file.");
        errorBox.exec();
        // We can't continue.
        return;
    }

    // Read the file into a QByteArray
    QByteArray clearBlob = file.readAll();

    qDebug() << "File contains " << clearBlob.length() << " bytes.";

    // Done with the file; close it.
    file.close();

    // Convert the key into a QByteArray
    QByteArray keyBlob = ui->keyLineEdit->text().toUtf8();

    qDebug() << "Key is " << keyBlob.length() << " bytes.";

    // XOR the file with the key
    QByteArray cryptBlob;
    // Give ourselves the memory before hand, so we don't call append() in the loop. It's slow.
    cryptBlob.resize(clearBlob.size());
    int blobPos;
    for (blobPos = 0; blobPos < clearBlob.length(); blobPos++)
    {
        // XOR each byte of the clearblob with the key, wrapping the key position around
        cryptBlob[blobPos] = clearBlob[blobPos] ^ keyBlob[blobPos % keyBlob.size()];
        //qDebug() << blobPos << ": " << clearBlob[blobPos] << " XOR " << keyBlob[blobPos % keyBlob.size()] << " (@ " << blobPos % keyBlob.size() << ")";
    }

    // Base64Encode the resulting encrypted QByteArray
    QString output = cryptBlob.toBase64(QByteArray::Base64Encoding | QByteArray::KeepTrailingEquals);

    // Give it to the user
    ui->dataTextEdit->setPlainText(output);

    // TODO: Give the user instructions on how to use the info
}

void FileEncrypt::on_decodeButton_clicked()
{
    // Check that there is a key in the key entry
    if (ui->keyLineEdit->text().isEmpty()) {
        QMessageBox errorBox;
        errorBox.setText("You must enter a key for decryption.");
        errorBox.setInformativeText("Make sure you have the correct key, or your result will be useless!");
        errorBox.exec();
        // We can't continue.
        return;
    }

    // Select a file - any file, even one that doesn't exist.
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString filename = dialog.getOpenFileName();

    // Check that we can open the file
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox errorBox;
        errorBox.setText("The file cannot be opened for writing.");
        errorBox.setInformativeText("There may be a permissions problem; ensure that you have the right to open and write the file.");
        errorBox.exec();
        // We can't continue.
        return;
    }

    // Read the input into a QByteArray (integral Base64Decode)
    QByteArray cryptBlob;
    cryptBlob = QByteArray::fromBase64(ui->dataTextEdit->toPlainText().simplified().remove(" ").remove("\n").toUtf8(), QByteArray::Base64Encoding | QByteArray::KeepTrailingEquals);
    qDebug() << "Input contains " << cryptBlob.length() << " bytes.";


    // Convert the key into a QByteArray
    QByteArray keyBlob = ui->keyLineEdit->text().toUtf8();

    // XOR the key with the decoded input
    QByteArray clearBlob;
    // Give ourselves the memory before hand, so we don't call append() in the loop. It's slow.
    clearBlob.resize(cryptBlob.size());
    int blobPos;
    for (blobPos = 0; blobPos < cryptBlob.length(); blobPos++)
    {
        // XOR each byte of the clearblob with the key, wrapping the key position around
        clearBlob[blobPos] = cryptBlob[blobPos] ^ keyBlob[blobPos % keyBlob.size()];
        //qDebug() << blobPos << ": " << cryptBlob[blobPos] << " XOR " << keyBlob[blobPos % keyBlob.size()] << " (@ " << blobPos % keyBlob.size() << ")";
    }


    // Save the result off to the file
    qint64 bytesWritten = file.write(clearBlob);
    qDebug() << "Wrote " << bytesWritten << " bytes.";

    // Done with the file
    file.close();

    // TODO: Inform user that we're done.
    QMessageBox successBox;
    successBox.setText("Decryption complete.");
    successBox.exec();
    // We're done!
    return;

}
