#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), result(0.0), symbol("=")
{
    ui->setupUi(this);

    // 设置数字按钮的连接
    setupConnections();

    // 设置运算符按钮的连接
    setupOperatorConnections();


    connect(ui->normalBtnC, &QPushButton::clicked, this, [&]() {
        ui->lineEdit->clear();
        result = 0.0;
        symbol="=";
        });

    connect(ui->normalBtnE, &QPushButton::clicked, this, [&]() {
        QString currentText = ui->lineEdit->text();
        double currentNumber = currentText.toDouble();

        if (symbol == "+") {
            result += currentNumber;
        }
        else if (symbol == "-") {
            result -= currentNumber;
        }
        else if (symbol == "*") {
            result *= currentNumber;
        }
        else if (symbol == "/") {
            if (currentNumber != 0) {
                result /= currentNumber;
            }
            else {
                ui->lineEdit->setText("Error: Div by 0");
                return;
            }
        }

        ui->lineEdit->setText(QString::number(result));  // 显示结果
        });
}


// 优化：使用数组和循环减少重复代码
void MainWindow::setupConnections() {
    // 数字按钮数组
    QPushButton* buttons[] = {
        ui->normalBtn0, ui->normalBtn1, ui->normalBtn2,
        ui->normalBtn3, ui->normalBtn4, ui->normalBtn5,
        ui->normalBtn6, ui->normalBtn7, ui->normalBtn8,
        ui->normalBtn9, ui->normalBtnP
    };

    // 数字按钮的对应字符数组
    QString digits[] = {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."
    };

    // 为每个数字按钮设置连接
    for (int i = 0; i < 11; ++i) {
        connect(buttons[i], &QPushButton::clicked, this, [=]() {
            QString currentText = ui->lineEdit->text();
            ui->lineEdit->setText(currentText + digits[i]);
            });
    }
}


// 创建一个通用的函数来处理运算符按钮点击事件
void MainWindow::setupOperatorConnections() {
    // 定义运算符按钮及其符号
    QPushButton* buttons[] = {
        ui->normalBtnA, ui->normalBtnS, ui->normalBtnM, ui->normalBtnD
    };
    QString operators[] = { "+", "-", "*", "/" };

    // 为每个运算符按钮设置连接
    for (int i = 0; i < 4; ++i) {
        connect(buttons[i], &QPushButton::clicked, this, [=]() {
            QString currentText = ui->lineEdit->text();
            if (!currentText.isEmpty()) {
                result = currentText.toDouble();  // 将当前文本转换为数字并保存到 result
            }
            symbol = operators[i];  // 设置当前运算符
            ui->lineEdit->clear();  // 清空输入框，准备接收下一个数字
            });
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

