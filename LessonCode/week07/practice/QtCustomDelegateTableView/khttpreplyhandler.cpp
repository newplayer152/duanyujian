#include"khttpreplyhandler.h"


KHttpReplyHandler::KHttpReplyHandler(QObject* parent)
    :QObject(parent)
{
}
KHttpReplyHandler::~KHttpReplyHandler()
{
    if (!photos.isEmpty())
        qDeleteAll(photos.begin(), photos.end());
}

void KHttpReplyHandler::onHandleHttpReply(  QNetworkReply* reply)
{

    if (reply->error() == QNetworkReply::NoError)
    {
        

        QByteArray responseData = reply->readAll();// 读取应答数据

        // 将字符串解析为 JSON  
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &parseError);

        // 检查 JSON 解析是否出错  
        if (parseError.error != QJsonParseError::NoError)
        {
            qWarning("Failed to parse JSON: %s", qPrintable(parseError.errorString()));
            return;
        }

        // 获取 JSON 数组  
        QJsonArray jsonArray = jsonDoc.array();

        // 遍历 JSON 数组  
        for (const QJsonValue& value : jsonArray)
        {
            QJsonObject obj = value.toObject();

            KPhotos* KPhoto = new KPhotos();


            // 提取 JSON 对象中的值
            KPhoto->m_albumId= obj["albumId"].toInt();
            KPhoto->m_id = obj["id"].toInt();
            KPhoto->m_title= obj["title"].toString();

            auto imageUrl=obj["url"].toString();

            // 创建 QNetworkAccessManager 来下载网络图片
            QNetworkAccessManager networkManager ;
            QUrl url(imageUrl);  // 创建 QUrl 对象
            QNetworkRequest request(url);  // 使用正确的构造函数
            // 异步下载图片
            QNetworkReply* reply = networkManager.get(request);

            // 创建一个事件循环，用于同步等待请求完成
            QEventLoop loop;

            // 连接 finished 信号到事件循环的 quit 槽
            QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

            // 开始事件循环，等待 reply 完成
            loop.exec();

            // 下载完成后，检查是否成功
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray imageData = reply->readAll();

                // 将下载的数据转换为 QPixmap
                if (KPhoto->m_pixmap.loadFromData(imageData)) {
                    qDebug() << "Image downloaded and loaded successfully!"<< imageUrl;
                }
                else {
                    qDebug() << "Failed to load image from network!"<< imageUrl;
                }
            }
            else {
                qDebug() << "Network error: " << reply->errorString();
            }

            // 清理资源
            reply->deleteLater();

        
            photos.push_back(KPhoto);

            
        }

    }
    

}