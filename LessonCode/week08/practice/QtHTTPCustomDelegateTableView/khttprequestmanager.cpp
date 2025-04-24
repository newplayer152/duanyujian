#include "khttprequestmanager.h"


KHttpRequestManager::KHttpRequestManager(QObject* parent)
    :QObject(parent)
{
    (void)connect(&m_httpManager, &QNetworkAccessManager::finished, this, &KHttpRequestManager::requestFinished);
}

KHttpRequestManager::~KHttpRequestManager()
{
}

void KHttpRequestManager::sendGetRequest(const QUrl& url)
{
    QNetworkRequest request(url);
    m_httpManager.get(request);
}

void KHttpRequestManager::sendPostRequest(const QUrl& url, const QByteArray& data)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_httpManager.post(request, data);
}