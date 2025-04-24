#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 为窗口安装事件过滤器
    this->installEventFilter(this);
}


void MainWindow::keyPressEvent(QKeyEvent* event) {

    // 检查是否按下了Ctrl键
    if (event->key() == Qt::Key_Control) {
        ui->showCtrlLabel->setText(u8"Ctrl 按下");
    }
};
void MainWindow::keyReleaseEvent(QKeyEvent* event) {

    // 检查是否松开了Ctrl键
    if (event->key() == Qt::Key_Control) {
        ui->showCtrlLabel->setText(u8"Ctrl 松开");
        
    }

};

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this )
    {
        if (event->type() == QEvent::Wheel)
        {
            QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
            if (wheelEvent->delta()>0)
            {
                ui->showWheelLabel->setText(u8"向上滚动");
            }
            else {
                ui->showWheelLabel->setText(u8"向下滚动");
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}
MainWindow::~MainWindow()
{
    delete ui;
}

