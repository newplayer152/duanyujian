#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTableWidget>




MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) // 确保 ui 被初始化
{
    ui->setupUi(this); // 设置 UI 界面
    // 设置窗口的最小尺寸
    this->setMinimumSize(800, 600); // 你可以根据需要调整尺寸

    // 设置主窗口
    setWindowTitle(u8"公司部门与员工信息");
    resize(600, 400);

    // 主部件和布局
    QWidget* mainWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(mainWidget);

    // 创建 QTreeWidget 展示部门信息
    QTreeWidget* treeWidget = new QTreeWidget();
    treeWidget->setHeaderLabel(u8"公司部门与员工信息");

    // 添加部门及员工数据到 QTreeWidget
    QTreeWidgetItem* devDept = new QTreeWidgetItem(treeWidget, QStringList(u8"研发部"));
    new QTreeWidgetItem(devDept, QStringList() << u8"张三 - 软件工程师");
    new QTreeWidgetItem(devDept, QStringList() <<u8"李四 - 算法研究员");

    QTreeWidgetItem* marketingDept = new QTreeWidgetItem(treeWidget, QStringList(u8"市场部"));
    new QTreeWidgetItem(marketingDept, QStringList() << u8"王五 - 市场专员");
    new QTreeWidgetItem(marketingDept, QStringList() << u8"赵六 - 营销经理");

    treeWidget->expandAll(); // 默认展开所有节点
    layout->addWidget(treeWidget);

    // 创建 QTableWidget 展示更详细的员工信息
    QTableWidget* tableWidget = new QTableWidget(4, 3); // 4 行，3 列
    tableWidget->setHorizontalHeaderLabels({ u8"姓名", u8"职位",u8"部门" });

    // 添加员工数据到 QTableWidget
    tableWidget->setItem(0, 0, new QTableWidgetItem(u8"张三"));
    tableWidget->setItem(0, 1, new QTableWidgetItem(u8"软件工程师"));
    tableWidget->setItem(0, 2, new QTableWidgetItem(u8"研发部"));

    tableWidget->setItem(1, 0, new QTableWidgetItem(u8"李四"));
    tableWidget->setItem(1, 1, new QTableWidgetItem(u8"算法研究员"));
    tableWidget->setItem(1, 2, new QTableWidgetItem(u8"研发部"));

    tableWidget->setItem(2, 0, new QTableWidgetItem(u8"王五"));
    tableWidget->setItem(2, 1, new QTableWidgetItem(u8"市场专员"));
    tableWidget->setItem(2, 2, new QTableWidgetItem(u8"市场部"));

    tableWidget->setItem(3, 0, new QTableWidgetItem(u8"赵六"));
    tableWidget->setItem(3, 1, new QTableWidgetItem(u8"营销经理"));
    tableWidget->setItem(3, 2, new QTableWidgetItem(u8"市场部"));

    layout->addWidget(tableWidget);

    // 设置主部件
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);


}

MainWindow::~MainWindow()
{
}
