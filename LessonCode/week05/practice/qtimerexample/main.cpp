
#include <QApplication>
#include <QWidget>
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>

class MyObject : public QWidget {
    Q_OBJECT

public:
    MyObject() {
         //启动内置定时器，设置时间间隔为5秒
        timerId = startTimer(5000);
        resize(100,100);
    }

protected:
    void timerEvent(QTimerEvent* event) override {
        if (event->timerId() == timerId) {
            resize(200, 200);// 5秒变大
            qDebug() << "Timer event occurred!";
            
        }
        return QWidget::timerEvent(event);
    }
private:
    int timerId;
    
};




int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MyObject obj;
    obj.show();
    return a.exec();
}

#include "main.moc"


