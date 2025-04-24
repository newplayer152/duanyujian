#ifndef _K_HTTP_REPLY_HANDLER_H_
#define _K_HTTP_REPLY_HANDLER_H_

#include "photostruct.h"
#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEventLoop>

class KHttpReplyHandler : public QObject
{
    Q_OBJECT
public:
    explicit KHttpReplyHandler(QObject* parent = nullptr);
    ~KHttpReplyHandler();

    void onHandleHttpReply(QNetworkReply* reply);

public:
    QVector<KPhotos*> photos;
};

#endif