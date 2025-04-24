#include <QApplication>
#include <QWidget>
#include <QEvent>

class MyWidget : public QWidget {
    Q_OBJECT
public:
    MyWidget() : QWidget() {
        // ���ó�ʼ���ڴ�С
        resize(initialWidth, initialHeight);
    }

protected:
    void enterEvent(QEvent* event) override {
        // ��������¼����Ŵ󴰿�
        resize(enlargedWidth, enlargedHeight);
        QWidget::enterEvent(event);
    }

    void leaveEvent(QEvent* event) override {
        // ����Ƴ��¼����ָ����ڴ�С
        resize(initialWidth, initialHeight);
        QWidget::leaveEvent(event);
    }

private:
    const int initialWidth = 100;  // ��ʼ���
    const int initialHeight = 50; // ��ʼ�߶�
    const int enlargedWidth = 200;  // �Ŵ���
    const int enlargedHeight = 100; // �Ŵ�߶�

};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MyWidget window;
    window.show();

    return app.exec();
}

#include "main.moc"
