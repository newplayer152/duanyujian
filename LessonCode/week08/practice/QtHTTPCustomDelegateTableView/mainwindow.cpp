#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	m_httpReqManger = new KHttpRequestManager(this);//����initDataSource���Զ��ͷ�
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
		emit dataLoaded(); // �������ݼ�����ɵ��ź�
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

	// ���õ���ѡ����
	//ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	//�رչ�����
	ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);




}