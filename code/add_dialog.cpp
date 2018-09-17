#include "add_dialog.h"
#include "ui_add_dialog.h"

#include <QVariantList>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>
#include <QChar>

Add_dialog::Add_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_dialog)
{
    ui->setupUi(this);
    this->setFixedSize(660,400);
}

Add_dialog::~Add_dialog()
{
    delete ui;
}

//增加新内容到数据库
void Add_dialog::on_pushButton_clicked()
{
    //对增加的内容格式是否符合标准进行检查
    int check = 0;

    //名字中不能含有数字
    if(ui->lineEdit_4->text().contains('1')||ui->lineEdit_4->text().contains('2')||ui->lineEdit_4->text().contains('3')||
            ui->lineEdit_4->text().contains('4')||ui->lineEdit_4->text().contains('5')||ui->lineEdit_4->text().contains('6')||
            ui->lineEdit_4->text().contains('7')||ui->lineEdit_4->text().contains('8')||ui->lineEdit_4->text().contains('9')||
            ui->lineEdit_4->text().contains('0'))
        check = 1;  //检查联系人是否符合要求
    if(ui->lineEdit_7->text().contains('1')||ui->lineEdit_7->text().contains('2')||ui->lineEdit_7->text().contains('3')||
            ui->lineEdit_7->text().contains('4')||ui->lineEdit_7->text().contains('5')||ui->lineEdit_7->text().contains('6')||
            ui->lineEdit_7->text().contains('7')||ui->lineEdit_7->text().contains('8')||ui->lineEdit_7->text().contains('9')||
            ui->lineEdit_7->text().contains('0'))
        check = 2;  //检查经费负责人是否符合要求
    if(ui->lineEdit_8->text().contains('1')||ui->lineEdit_8->text().contains('2')||ui->lineEdit_8->text().contains('3')||
            ui->lineEdit_8->text().contains('4')||ui->lineEdit_8->text().contains('5')||ui->lineEdit_8->text().contains('6')||
            ui->lineEdit_8->text().contains('7')||ui->lineEdit_8->text().contains('8')||ui->lineEdit_8->text().contains('9')||
            ui->lineEdit_8->text().contains('0'))
        check = 3;  //检查经办人是否符合要求
    if(ui->lineEdit_9->text().contains('1')||ui->lineEdit_9->text().contains('2')||ui->lineEdit_9->text().contains('3')||
            ui->lineEdit_9->text().contains('4')||ui->lineEdit_9->text().contains('5')||ui->lineEdit_9->text().contains('6')||
            ui->lineEdit_9->text().contains('7')||ui->lineEdit_9->text().contains('8')||ui->lineEdit_9->text().contains('9')||
            ui->lineEdit_9->text().contains('0'))
        check = 4;  //检查验收人是否符合要求
    if(ui->lineEdit_10->text().contains('1')||ui->lineEdit_10->text().contains('2')||ui->lineEdit_10->text().contains('3')||
            ui->lineEdit_10->text().contains('4')||ui->lineEdit_10->text().contains('5')||ui->lineEdit_10->text().contains('6')||
            ui->lineEdit_10->text().contains('7')||ui->lineEdit_10->text().contains('8')||ui->lineEdit_10->text().contains('9')||
            ui->lineEdit_10->text().contains('0'))
        check = 5;  //检查使用人是否符合要求
    //电话号码必须为13位以内，只包含数字和下划线
    if(ui->lineEdit_3->text().length() > 13 || !(isCardNumber(ui->lineEdit_3->text())))
        check = 6;
    //卡号必须为20位以内，只包含数字和下划线
    if(ui->lineEdit_6->text().length() >= 20 || !(isCardNumber(ui->lineEdit_6->text())))
        check = 7;
    //基本配置信息不能过长
    if(ui->textEdit->toPlainText().length()>100)
        check = 8;
    //经费只能为数字
    if(!(isnumber(ui->lineEdit_5->text())))
        check = 9;
    //设备编号不能超过20位
    if(ui->lineEdit_11->text().length() > 20)
        check = 10;
    //lineEdit和配置信息不允许为空
    if(ui->lineEdit_11->text()==""||ui->lineEdit_10->text()==""||ui->lineEdit_9->text()==""||ui->lineEdit_8->text()==""||
            ui->lineEdit_7->text()==""||ui->lineEdit_6->text()==""||ui->lineEdit_5->text()==""||
            ui->lineEdit_4->text()==""||ui->lineEdit_3->text()==""||ui->lineEdit_2->text()==""||ui->textEdit->toPlainText()==""||
            ui->lineEdit->text()=="")
        check = 11;

    switch (check) {
    case 1:
        QMessageBox::information(0,"错误型号1","联系人姓名格式存在错误\n可能含有数字\n");
        break;
    case 2:
        QMessageBox::information(0,"错误型号2","经费负责人姓名格式存在错误\n可能含有数字\n");
        break;
    case 3:
        QMessageBox::information(0,"错误型号3","经办人姓名格式存在错误\n可能含有数字\n");
        break;
    case 4:
        QMessageBox::information(0,"错误型号4","验收人姓名格式存在错误\n可能含有数字\n");
        break;
    case 5:
        QMessageBox::information(0,"错误型号5","使用人姓名格式存在错误\n可能含有数字\n");
        break;
    case 6:
        QMessageBox::information(0,"错误型号6","电话号码必须为13位以内，只包含数字和下划线");
        break;
    case 7:
        QMessageBox::information(0,"错误型号7","卡号必须为20位以内，只包含数字和下划线");
        break;
    case 8:
        QMessageBox::information(0,"错误型号8","基本配置信息不能超过100个字符");
    case 9:
        QMessageBox::information(0,"错误型号9","经费只能为数字");
        break;
    case 10:
        QMessageBox::information(0,"错误型号10","设备编号不能超过20位");
        break;
    case 11:
        QMessageBox::information(0,"错误型号11","除备注外不允许存在空值属性");
        break;
    default:
        break;
    }


    if(check == 0){
        this->hide();
        //连接数据库.并将框中的数据写入数据库
        QSqlQuery query;
        QString pose[] = {ui->lineEdit->text(),
              ui->comboBox->currentText(),
              ui->textEdit->toPlainText(),
              ui->dateEdit->text(),
              ui->dateEdit_2->text(),

              ui->lineEdit_2->text(),
              ui->lineEdit_3->text(),
              ui->lineEdit_4->text(),
              ui->lineEdit_5->text(),
              ui->lineEdit_6->text(),
              ui->comboBox_2->currentText(),

              ui->lineEdit_7->text(),
              ui->lineEdit_8->text(),
              ui->lineEdit_9->text(),

              ui->lineEdit_10->text(),
              ui->dateEdit_3->text(),

              ui->comboBox_3->currentText(),
              ui->textEdit_2->toPlainText(),

              ui->lineEdit_11->text(),
             };
        //从表单中获取数据，执行插入数据语句
        query.prepare("INSERT INTO equipment_information("
                 "name,types,basic_configuration,date_of_purchase,date_of_manufacture,"
                 "supplier,phone,contact_person,cost,money_card_number,type_of_funding,"
                 "person_in_charge,manager,acceptance,user,"
                 "delivery_date,state_of_use,remarks, equipment_ID)"
                 "VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");

        QVariantList names; //1
        names << pose[0];
        query.addBindValue(names);
        QVariantList types; //2
        types << pose[1];
        query.addBindValue(types);
        QVariantList basic_cons; //3
        basic_cons << pose[2];
        query.addBindValue(basic_cons);
        QVariantList date_of_purs; //4
        date_of_purs << pose[3];
        query.addBindValue(date_of_purs);
        QVariantList date_of_mans; //5
        date_of_mans << pose[4];
        query.addBindValue(date_of_mans);
        QVariantList suppliers; //6
        suppliers << pose[5];
        query.addBindValue(suppliers);
        QVariantList phones; //7
        phones << pose[6];
        query.addBindValue(phones);
        QVariantList contact_pers; //8
        contact_pers << pose[7];
        query.addBindValue(contact_pers);
        QVariantList cost; //9
        cost << pose[8];
        query.addBindValue(cost);
        QVariantList money_card_number;
        money_card_number << pose[9];//10
        query.addBindValue(money_card_number);
        QVariantList type_of_funds;  //11
        type_of_funds << pose[10];
        query.addBindValue(type_of_funds);
        QVariantList person_in_chars;  //12
        person_in_chars << pose[11];
        query.addBindValue(person_in_chars);
        QVariantList managers;  //13
        managers << pose[12];
        query.addBindValue(managers);
        QVariantList acceptances; //14
        acceptances <<pose[13];
        query.addBindValue(acceptances);
        QVariantList users;  //15
        users << pose[14];
        query.addBindValue(users);

        QVariantList delivery_dates; //16
        delivery_dates <<pose[15];
        query.addBindValue(delivery_dates);
        QVariantList state_of_uses;  //17
        state_of_uses << pose[16];
        query.addBindValue(state_of_uses);
        QVariantList remarks;  //18
        remarks <<pose[17];
        query.addBindValue(remarks);
        QVariantList equipment_ID;  //19
        equipment_ID <<pose[18];
        query.addBindValue(equipment_ID);

        if(!query.execBatch()){
            QMessageBox::critical(0,QObject::tr("Error2"),query.lastError().text());
        }
        query.finish();//插入错误时报错
    }
}

void Add_dialog::on_pushButton_2_clicked()
{
    this->close();//点击取消时关闭窗口
}
