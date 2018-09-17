#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextEdit>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QLineEdit>
#include <QSqlError>
#include <QVBoxLayout>
#include <QWidget>
#include <QTextDocument>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QStandardItemModel>
#include <QComboBox>
#include <QPushButton>
#include "search.h"
#include "add_dialog.h"
#include "edit_dialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void doPrint();//打印
    void doPrintPreview();//打印预览
    void doCreatePdf();//创建pdf
    void doCloseApplication();//关闭程序
    void printDocument(QPrinter *printer);//打印文件
    void doDelete();//删除数据
    void createTable();//创建表格
    void openTable();//打开表格
    void doHelp();//显示相关信息
    void saveData();//保存数据
    void doSelect();//查找数据
    void addData();//添加数据
    void cancelSearch();//取消显示查找
    void editData();//编辑数据
    void displaySearch();//显示查找

private:
    Ui::MainWindow *ui;
    QTableView *view;
    QSqlTableModel *model;
    QWidget* widget;
    QLineEdit* lineEdit;
    QVBoxLayout* layout;
    QComboBox*  combobox ;
    QPushButton* buttonCancel;
    QPushButton* buttonSearch;
    QHBoxLayout *hlayout;
    Add_dialog Add;
    Edit_dialog Edit;
    Password_dialog database_connect;
    int isOpened = 0;//判断表是否打开
    int isSelect = 0;//判断某一列是否被选中
    void createComboBOX();//创建下拉选项

};

#endif // MAINWINDOW_H
