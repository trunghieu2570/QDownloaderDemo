#ifndef QDOWNLOADMANAGER_H
#define QDOWNLOADMANAGER_H

#include "qdownload.h"

#include <QObject>

class QDownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit QDownloadManager(QObject *parent = nullptr);

private:
    QList<QDownload*> segments;
    QDownload* createDownload(QString url, QFile *file, int id, qint64 start, qint64 end, qint64 total);

public slots:
    void createSegments(QString url, QString fileName, qint64 fileSize);
    void startDownload();
    void segmentFinished();

signals:

};


#endif // QDOWNLOADMANAGER_H
