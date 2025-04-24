#ifndef __K_HTTP_REQUEST_MANAGER_H_
#define __K_HTTP_REQUEST_MANAGER_H_

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
class KHttpRequestManager : public QObject
{
    Q_OBJECT
public:
    KHttpRequestManager(QObject* parent = nullptr);
    ~KHttpRequestManager();

    void sendGetRequest(const QUrl& url);
    void sendPostRequest(const QUrl& url, const QByteArray& data);
signals:
    void requestFinished(QNetworkReply* reply);//这里不要使用前置声明，会导致找不到 QNetworkReply
    
private:
    QNetworkAccessManager m_httpManager;
};

#endif