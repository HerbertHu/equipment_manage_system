#include "password_dialog.h"
#include "ui_password_dialog.h"

Password_dialog::Password_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Password_dialog)
{
    ui->setupUi(this);
    this->setFixedSize(260,180);//设置窗口大小
    isConnected = 0;
    ui->LineEdit_3->setEchoMode(QLineEdit::Password);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(connectMysql()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(closeWindow()));
}

Password_dialog::~Password_dialog()
{
    delete ui;
}

int Password_dialog::connectMysql()
{
    QString databaseName = ui->LineEdit->text();
    QString userName = ui->LineEdit_2->text();
    QString password = ui->LineEdit_3->text();

    QSqlDatabase db;//连接数据库
    if(QSqlDatabase::contains("qt_sql_default_connection"))//数据库已经存在，使用已选择的数据库
        db = QSqlDatabase::database("qt_sql_default_connection");
    else{
        db = QSqlDatabase::addDatabase("QMYSQL");//使用MySQL数据库
        db.setHostName("localhost");
        db.setPort(3306);
        db.setDatabaseName(databaseName);
        db.setUserName(userName);
        db.setPassword(password);
    }

    if (!db.open())//数据库未打开时报错
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),
        db.lastError().text());
        QSqlDatabase db = QSqlDatabase::database();//获得实例
        QString name = db.connectionName();//获得默认连接名
        QSqlDatabase::removeDatabase(name);//删除默认连接
        return 0;
    }
    else{
        this->databaseCreateTable();
        QMessageBox::about(NULL, "提示", "数据库连接成功");
        this->close();
        isConnected = 1;
        return 1;
    }

}

void Password_dialog::databaseCreateTable()
{
    QSqlQuery query;
    //判断数据库是否已存在表
    query.prepare("SELECT TABLE_NAME FROM information_schema.TABLES WHERE TABLE_NAME ='equipment_information'");

    query.exec();

    if(!query.next()){
    //创建数据库表
        query.prepare("CREATE TABLE equipment_information("
                      "id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(40),"
                    "types CHAR(10), basic_configuration VARCHAR(100),"
                    "date_of_purchase DATE, date_of_manufacture DATE, equipment_ID VARCHAR(20),"
                    "supplier VARCHAR(40), phone VARCHAR(14), contact_person VARCHAR(30),"
                    "cost VARCHAR(20),money_card_number VARCHAR(20), type_of_funding VARCHAR(10),"
                    "person_in_charge VARCHAR(30),manager VARCHAR(30),acceptance VARCHAR(30),"
                    "user VARCHAR(30), delivery_date DATE,state_of_use CHAR(20), remarks VARCHAR(200))");
        //创建失败时报错
        if (!query.exec())
        {
            QMessageBox::critical(0, QObject::tr("Create table error"),
                                  query.lastError().text());
        }
    }
}

void Password_dialog::closeWindow()
{
    this->close();//点击取消时关闭窗口
}
