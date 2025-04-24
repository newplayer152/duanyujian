#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "photostruct.h"
#include "kphototablemodel.h"
#include "kcomboxdelegate.h"
#include "khttpreplyhandler.h"
#include "khttprequestmanager.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
	void dataLoaded(); // ÐÂÔöÐÅºÅ
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	void initDataSource();
	void initTableView();

private:
    Ui::MainWindow *ui;
	KPhotoTableModel* m_pModel = nullptr;
	KComboxDelegate* m_pComboxDelegate = nullptr;
	KHttpRequestManager* m_httpReqManger;
	KHttpReplyHandler* m_httpReplyHandler;
};
#endif // MAINWINDOW_H
