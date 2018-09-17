#ifndef EDIT_DIALOG_H
#define EDIT_DIALOG_H

#include <QDialog>
#include <password_dialog.h>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QDate>

namespace Ui {
class Edit_dialog;
}

class Edit_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Edit_dialog(QWidget *parent = 0);
    ~Edit_dialog();

    QString getID;
    QSqlTableModel* editModel;

    //传递信号的函数
    void getMyid(QString number)
    {
        getID = number;
    }

    //更新主窗口的表格
    void setWindowModel(QSqlTableModel* windowModel)
    {
        editModel = windowModel;
    }

    //修改数据的函数
    void change();

    //检测一个字符串是否为纯数字的函数
    bool isnumber(const QString s){
        int i = s.length();
        for(int j=0;j<i;j++)
        {
            if(s[j]>'9' || s[j]<'0')
                return false;
        }
        return true;
    }

    bool isCardNumber(const QString s){
        int i = s.length();
        for(int j=0;j<i;j++)
        {
            if((s[j]>='0' && s[j]<='9') || s[j] =='_')
                return true;
        }
        return false;
    }

private slots:
    void on_pushButton_clicked();

private:
    Ui::Edit_dialog *ui;
};

#endif // EDIT_DIALOG_H
