#ifndef PASSWORD_DIALOG_H
#define PASSWORD_DIALOG_H

#include <QDialog>
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class Password_dialog;
}

class Password_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Password_dialog(QWidget *parent = 0);
    ~Password_dialog();

    Password_dialog* password_window;
    void setPassword(Password_dialog* inputPassword)
    {
     password_window = inputPassword;
    }
    bool isConnected;

public slots:
    int connectMysql();
    void databaseCreateTable();
    void closeWindow();

private:
    Ui::Password_dialog *ui;
};

#endif // PASSWORD_DIALOG_H
