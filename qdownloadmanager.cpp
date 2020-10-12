#include "qdownloadmanager.h"

QDownloadManager::QDownloadManager(QObject *parent) : QObject(parent)
{

}

QDownload* QDownloadManager::createDownload(QString url, QFile *file, int id, qint64 start, qint64 end, qint64 total)
{
    QDownload *dl = new QDownload();
    dl->setTarget(url);
    dl->setRange(start, end);
    dl->setId(id);
    dl->setFile(file);
    dl->setTotal(total);
    return dl;
}

void QDownloadManager::createSegments(QString url, QString fileName, qint64 fileSize)
{
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly))
        return;
    qint64 s_size = fileSize / 8;
    for (int i = 0; i < 7; i++) {
        segments.append(createDownload(url, file, i, i * s_size, (i + 1) * s_size - 1, fileSize));
    }
    segments.append(createDownload(url, file, 7, 7 * s_size, fileSize, fileSize));
}
