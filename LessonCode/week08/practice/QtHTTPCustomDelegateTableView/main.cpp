#include "mainwindow.h"
#include "khttpreplyhandler.h"
#include "khttprequestmanager.h"
#include <QApplication>
#include <QDebug>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
