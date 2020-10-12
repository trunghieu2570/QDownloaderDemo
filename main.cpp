#include <QCoreApplication>
#include <QThread>
#include <QtCore>
#include <QtConcurrent>
#include <QList>
#include "qdownload.h"


void createDownload(QString url, QFile *file, int id, qint64 start, qint64 end, qint64 total)
{
    QDownload *dl = new QDownload();
    dl->setTarget(url);
    dl->setRange(start, end);
    dl->setId(id);
    dl->setFile(file);
    dl->setTotal(total);
    dl->download();
}

void createSegments(QString url, QString fileName, qint64 fileSize)
{
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly))
        return;
    qint64 s_size = fileSize / 8;
    for (int i = 0; i < 7; i++) {

        createDownload(url, file, i, i * s_size, (i + 1) * s_size - 1, fileSize);
    }
    createDownload(url, file, 7, 7 * s_size, fileSize, fileSize);

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << QSslSocket::sslLibraryVersionString();
    createSegments("https://download.virtualbox.org/virtualbox/6.1.14/VirtualBox-6.1.14-140239-Win.exe", "file.exe", 108007440);
    qDebug() << "passed";
    return a.exec();
}
