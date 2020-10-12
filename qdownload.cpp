#include "qdownload.h"

QDownload::QDownload(QObject *parent) : QObject(parent)
{
    QObject::connect(&qnam, SIGNAL(finished(QNetworkReply*)),this, SLOT(downloadFinish(QNetworkReply*)));
}

QDownload::~QDownload()
{
    //if (rep != 0)
    //    delete rep;
}

void QDownload::setTarget(const QString &t)
{
    this->target = t;
}

void QDownload::setRange(qint64 start, qint64 end) {
    this->start = start;
    this->end = end;
}

void QDownload::setId(int id)
{
    this->num = id;
}

void QDownload::setFile(QFile *file)
{
    this->file = file;
}

void QDownload::setTotal(qint64 total)
{
    this->total = total;
}

void QDownload::download()
{
    QUrl url = QUrl::fromEncoded(this->target.toLocal8Bit());
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setRawHeader("Range", QString("bytes=%1-%2").arg(QString::number(start), QString::number(end)).toLocal8Bit());
    rep = qnam.get(request);
    state = STARTED;
    connect(rep, &QNetworkReply::finished, this, &QDownload::replyFinish);
    connect(rep, &QNetworkReply::readyRead, this, &QDownload::downloadReadyRead);
    connect(rep, &QNetworkReply::downloadProgress, this, &QDownload::downloadProgress);
    connect(rep, &QNetworkReply::sslErrors, this, &QDownload::downloadSslErrors);
    qDebug() << "segment:" << num << start << end;
}

void QDownload::downloadFinish(QNetworkReply *data)
{
    file->seek(start);
    file->write(data->readAll());
    state = FINISHED;
    emit finished();
    data->deleteLater();
    qDebug() << "finished:" << num;
}

void QDownload::replyFinish()
{
}

void QDownload::downloadProgress(qint64 rev, qint64 total)
{
    qDebug() << file->fileName() << num << rev << total << QThread::currentThread();
}

void QDownload::downloadSslErrors(const QList<QSslError> &errors)
{
    for(QSslError e : errors)
    {
        qDebug() << e.errorString();
    }
}


void QDownload::downloadReadyRead()
{
    //qDebug() << "rd";
}
