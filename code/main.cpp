#include "mainwindow.h"
#include "password_dialog.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTableWidget>
#include <QDebug>
#include <QtSql>
#include <QApplication>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    //创建应用
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");

    MainWindow w;
    //设置主窗口的显示与名字
    w.setWindowTitle("实验室器材管理系统");
    w.show();

    return a.exec();
}
