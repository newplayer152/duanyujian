#include <QApplication>
#include <QWidget>
#include <QEvent>

class MyWidget : public QWidget {
    Q_OBJECT
public:
    MyWidget() : QWidget() {
        // 设置初始窗口大小
        resize(initialWidth, initialHeight);
    }

protected:
    void enterEvent(QEvent* event) override {
        // 鼠标移入事件，放大窗口
        resize(enlargedWidth, enlargedHeight);
        QWidget::enterEvent(event);
    }

    void leaveEvent(QEvent* event) override {
        // 鼠标移出事件，恢复窗口大小
        resize(initialWidth, initialHeight);
        QWidget::leaveEvent(event);
    }

private:
    const int initialWidth = 100;  // 初始宽度
    const int initialHeight = 50; // 初始高度
    const int enlargedWidth = 200;  // 放大宽度
    const int enlargedHeight = 100; // 放大高度

};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MyWidget window;
    window.show();

    return app.exec();
}

#include "main.moc"
