#include <QCoreApplication>
#include <QObject>
#include <QDebug>

// 发送者类
class Sender : public QObject {
    Q_OBJECT

public:
    void emitSignal() {
        qDebug() << "Sender: Emitting signal...";
        emit mySignal("Hello from Sender!");
    }

signals:
    void mySignal(const QString& message);  // 自定义信号
};

// 接收者类
class Receiver : public QObject {
    Q_OBJECT

public slots:
    void handleSignal(const QString& message) {
        qDebug() << "Receiver: Received signal with message:" << message;
    }
};

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    Sender sender;
    Receiver receiver;

    // 连接信号和槽
    QObject::connect(&sender, &Sender::mySignal, &receiver, &Receiver::handleSignal);

    // 触发信号
    sender.emitSignal();

    return app.exec();
}

#include "main.moc"