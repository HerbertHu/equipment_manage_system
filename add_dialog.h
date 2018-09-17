#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <password_dialog.h>

namespace Ui {
class Add_dialog;
}

class Add_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_dialog(QWidget *parent = 0);
    ~Add_dialog();

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
    void on_pushButton_2_clicked();

private:
    Ui::Add_dialog *ui;
};

#endif // ADD_DIALOG_H
