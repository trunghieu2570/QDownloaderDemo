#ifndef QDOWNLOAD_H
#define QDOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QFile>
#include <QThread>
#include <QReadWriteLock>

enum QDownloadState {
    FINISHED,
    STARTED,
    ERROR,
};

class QDownload : public QObject
{
    Q_OBJECT
public:
    explicit QDownload(QObject *parent = nullptr);
    ~QDownload();
    void setTarget(const QString&);
    void setRange(qint64, qint64);
    void setId(int id);
    void setFile(QFile *);
    void setTotal(qint64);
private:
    QNetworkAccessManager qnam;
    QDownloadState state;
    QFile* file;
    QNetworkReply* rep = nullptr;
    QString target;
    int num = 0;
    qint64 total;
    qint64 start, end;
public slots:
    void download();
    void downloadFinish(QNetworkReply*);
    void replyFinish();
    void downloadProgress(qint64, qint64);
    void downloadSslErrors(const QList<QSslError> &);
    void downloadReadyRead();

signals:
    void finished();
};

#endif // QDOWNLOAD_H
