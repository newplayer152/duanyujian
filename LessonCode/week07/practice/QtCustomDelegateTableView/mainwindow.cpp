#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	m_httpReqManger = new KHttpRequestManager(this);//放入initDataSource会自动释放
	m_httpReplyHandler = new KHttpReplyHandler(this);
    initDataSource();

	(void)QObject::connect(this, &MainWindow::dataLoaded, this, [=]() {
			initTableView();
		});
    
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initDataSource()
{

	(void)QObject::connect(m_httpReqManger, &KHttpRequestManager::requestFinished, this, [=](QNetworkReply* reply) {
		m_httpReplyHandler->onHandleHttpReply(reply);
		emit dataLoaded(); // 发出数据加载完成的信号
		});
	m_httpReqManger->sendGetRequest(QUrl("http://jsonplaceholder.typicode.com/photos?albumId=5"));

}

void MainWindow::initTableView()
{


	m_pModel = new KPhotoTableModel(this);
	m_pModel->setContent(m_httpReplyHandler->photos);
	m_pComboxDelegate = new KComboxDelegate(this);
	ui->tableView->setItemDelegate(m_pComboxDelegate);

	ui->tableView->setModel(m_pModel);

	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui->tableView->verticalHeader()->hide();

	// 设置单击选中行
	//ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	//关闭滚动条
	ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);




}