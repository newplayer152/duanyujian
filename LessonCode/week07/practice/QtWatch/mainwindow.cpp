#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QtMath>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) // 确保 ui 被初始化
{
    ui->setupUi(this); // 设置 UI 界面

    // 设置窗口的最小尺寸
    this->setMinimumSize(600, 600);

    // 设置定时器每秒更新一次时钟
    QTimer* m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(update()));

    m_pTimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui; // 确保 ui 被正确删除
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 启用抗锯齿
    painter.translate(width() / 2, height() / 2);   // 将坐标系原点移到窗口中心

    int side = qMin(width(), height());
    painter.scale(side / 200.0, side / 200.0);      // 根据窗口大小进行缩放

    QTime time = QTime::currentTime();  // 获取当前时间

    // 绘制时钟表盘
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255)); // 设置白色背景
    painter.drawEllipse(-90, -90, 180, 180);  // 绘制外圆

    // 绘制时针
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    QColor hourColor(127, 0, 127);  // 设置时针为紫色
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();  // 保存当前画笔状态
    painter.rotate(30.0 * (time.hour() + time.minute() / 60.0));  // 根据时间旋转时针
    painter.drawConvexPolygon(hourHand, 3);  // 绘制时针
    painter.restore();  // 恢复画笔状态

    // 绘制分针
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };
    painter.setBrush(QColor(0, 127, 255));  // 设置分针为蓝色
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));  // 根据时间旋转分针
    painter.drawConvexPolygon(minuteHand, 3);  // 绘制分针
    painter.restore();

    // 绘制秒针
    static const QPoint secondHand[3] = {
        QPoint(1, 1),
        QPoint(-1, 1),
        QPoint(0, -90)
    };
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 0, 0));  // 设置秒针为红色
    painter.save();
    painter.rotate(6.0 * time.second());  // 根据时间旋转秒针
    painter.drawConvexPolygon(secondHand, 3);  // 绘制秒针
    painter.restore();

    // 绘制时钟刻度
    painter.setPen(QPen(Qt::black));
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);  // 绘制小时刻度
        painter.rotate(30.0);  // 每次旋转 30°，对应下一个小时刻度
    }

    // 绘制分钟刻度（较小的刻度）
    painter.setPen(QPen(Qt::black));
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0) {
            painter.drawLine(92, 0, 96, 0);  // 绘制分钟刻度（每隔 1 分钟）
        }
        painter.rotate(6.0);  // 每次旋转 6°，对应下一个分钟刻度
    }

    // 绘制小时数字
    QFont font = painter.font();
    font.setPixelSize(12);  // 设置字体大小
    painter.setFont(font);
    for (int i = 0; i < 12; ++i) {
        // 设置数字的位置，使其出现在圆圈的外侧
        QString number = QString::number(i + 1);  // 将数字转换为字符串
        painter.save();
        painter.rotate(i * 30 );  // 每隔 30° 旋转，定位到相应的小时
        painter.drawText(35, -70, number);  // 在正确的位置绘制数字
        painter.restore();
    }


    //// 绘制小时数字
    //QFont font = painter.font();
    //font.setPixelSize(12);  // 设置字体大小
    //painter.setFont(font);

    //for (int i = 0; i < 12; ++i) {
    //    QString number = QString::number(i + 1);  // 将数字转换为字符串

    //    // 保存当前状态
    //    painter.save();

    //    // 旋转画布，使得数字在正确位置
    //    painter.rotate(i * 30);  // 每隔 30° 旋转，定位到相应的小时

    //    // 绘制数字，数字位置的 x 和 y 需要是相对于圆心的
    //    int radius = 70;  // 距离圆心的半径
    //    int x = radius * qCos(qDegreesToRadians(i * 15.0));  // 计算 x 坐标
    //    int y = radius * qSin(qDegreesToRadians(i * 15.0));  // 计算 y 坐标

    //    // 绘制数字（通过 offset 来确保文字始终是正向的）
    //    painter.drawText(x - 6, y + 6, number);  // 调整偏移量来使数字居中

    //    // 恢复画布的状态
    //    painter.restore();
    //}

}
