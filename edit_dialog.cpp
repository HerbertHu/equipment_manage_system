#include "edit_dialog.h"
#include "ui_edit_dialog.h"

Edit_dialog::Edit_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit_dialog)
{
    ui->setupUi(this);
    this->setFixedSize(660,400);//设置窗口大小
}

Edit_dialog::~Edit_dialog()
{
    delete ui;
}

void Edit_dialog::change()//获取数据库中原有的数据
{
    //利用获取到的ID进行查询
    QSqlTableModel model;
    model.setTable("equipment_information");
    model.setFilter("id =" + getID);
    model.select();
    QString a[19];

    //从数据库中提取数据
    for(int i=0; i<model.rowCount() ; i++){
        QSqlRecord record = model.record(i);
        a[0] = record.value("name").toString();
        a[1] = record.value("types").toString();
        a[2] = record.value("basic_configuration").toString();
        a[3] = record.value("date_of_purchase").toString();
        a[4] = record.value("date_of_manufacture").toString();
        a[5] = record.value("supplier").toString();
        a[6] = record.value("phone").toString();
        a[7] = record.value("contact_person").toString();
        a[8] = record.value("cost").toString();
        a[9] = record.value("money_card_number").toString();
        a[10] = record.value("type_of_funding").toString();
        a[11] = record.value("person_in_charge").toString();
        a[12] = record.value("manager").toString();
        a[13] = record.value("acceptance").toString();
        a[14] = record.value("user").toString();
        a[15] = record.value("delivery_date").toString();
        a[16] = record.value("state_of_use").toString();
        a[17] = record.value("remarks").toString();
        a[18] = record.value("equipment_ID").toString();
    }

    //QByteArray ba(a[3].toLatin1());
    //qWarning("lalal %s",ba.data());

    //将获取到的内容放入表格中
    QDate dt;
    ui->lineEdit_11->setText(a[0]);
    ui->comboBox_4->setCurrentText(a[1]);
    ui->textEdit_3->setText(a[2]);
    dt = QDate::fromString(a[3],"yyyy-MM-dd");
    ui->dateEdit_4->setDate(dt);
    dt = QDate::fromString(a[4],"yyyy-MM-dd");
    ui->dateEdit_5->setDate(dt);
    ui->lineEdit_12->setText(a[5]);
    ui->lineEdit_13->setText(a[6]);
    ui->lineEdit_14->setText(a[7]);
    ui->lineEdit_15->setText(a[8]);
    ui->lineEdit_16->setText(a[9]);
    ui->comboBox_5->setCurrentText(a[10]);
    ui->lineEdit_17->setText(a[11]);
    ui->lineEdit_18->setText(a[12]);
    ui->lineEdit_19->setText(a[13]);
    ui->lineEdit_20->setText(a[14]);

    dt = QDate::fromString(a[15],"yyyy-MM-dd");
    ui->dateEdit_6->setDate(dt);
    ui->comboBox_6->setCurrentText(a[16]);
    ui->textEdit_4->setPlainText(a[17]);

    ui->lineEdit->setText(a[18]);

}

//点击修改后执行判断与插入
void Edit_dialog::on_pushButton_clicked()
{
    //连接数据库前先进行判断数据内容是否符合标准
    int check = 0;

    //名字中不能含有数字
    if(ui->lineEdit_14->text().contains('1')||ui->lineEdit_14->text().contains('2')||ui->lineEdit_14->text().contains('3')||
            ui->lineEdit_14->text().contains('4')||ui->lineEdit_14->text().contains('5')||ui->lineEdit_14->text().contains('6')||
            ui->lineEdit_14->text().contains('7')||ui->lineEdit_14->text().contains('8')||ui->lineEdit_14->text().contains('9')||
            ui->lineEdit_14->text().contains('0'))
        check = 1;  //检查联系人是否符合标准
    if(ui->lineEdit_17->text().contains('1')||ui->lineEdit_17->text().contains('2')||ui->lineEdit_17->text().contains('3')||
            ui->lineEdit_17->text().contains('4')||ui->lineEdit_17->text().contains('5')||ui->lineEdit_17->text().contains('6')||
            ui->lineEdit_17->text().contains('7')||ui->lineEdit_17->text().contains('8')||ui->lineEdit_17->text().contains('9')||
            ui->lineEdit_17->text().contains('0'))
        check = 2;  //检查经费负责人是否符合标准
    if(ui->lineEdit_18->text().contains('1')||ui->lineEdit_18->text().contains('2')||ui->lineEdit_18->text().contains('3')||
            ui->lineEdit_18->text().contains('4')||ui->lineEdit_18->text().contains('5')||ui->lineEdit_18->text().contains('6')||
            ui->lineEdit_18->text().contains('7')||ui->lineEdit_18->text().contains('8')||ui->lineEdit_18->text().contains('9')||
            ui->lineEdit_18->text().contains('0'))
        check = 3;  //检查经办人是否符合标准
    if(ui->lineEdit_19->text().contains('1')||ui->lineEdit_19->text().contains('2')||ui->lineEdit_19->text().contains('3')||
            ui->lineEdit_19->text().contains('4')||ui->lineEdit_19->text().contains('5')||ui->lineEdit_19->text().contains('6')||
            ui->lineEdit_19->text().contains('7')||ui->lineEdit_19->text().contains('8')||ui->lineEdit_19->text().contains('9')||
            ui->lineEdit_19->text().contains('0'))
        check = 4;  //检查验收人是否符合标准
    if(ui->lineEdit_20->text().contains('1')||ui->lineEdit_20->text().contains('2')||ui->lineEdit_20->text().contains('3')||
            ui->lineEdit_20->text().contains('4')||ui->lineEdit_20->text().contains('5')||ui->lineEdit_20->text().contains('6')||
            ui->lineEdit_20->text().contains('7')||ui->lineEdit_20->text().contains('8')||ui->lineEdit_20->text().contains('9')||
            ui->lineEdit_20->text().contains('0'))
        check = 5;  //检查使用人是否符合标准
    //电话号码必须为13位以内，只包含数字和下划线
    if(ui->lineEdit_13->text().length() > 13 || !(isCardNumber(ui->lineEdit_13->text())))
        check = 6;
    //卡号必须为20位以内，只包含数字和下划线
    if(ui->lineEdit_16->text().length() > 20 || !(isCardNumber(ui->lineEdit_16->text())))
        check = 7;
    //基本配置信息不能过长
    if(ui->textEdit_3->toPlainText().length() > 100)
        check = 8;
    //经费只能为数字
    if(!(isnumber(ui->lineEdit_15->text())))
        check = 9;
    //设备编号不能超过20位
    if(ui->lineEdit->text().length() > 20)
        check = 10;
    //有信息为空
    if(ui->lineEdit_11->text()==""||ui->lineEdit_12->text()==""||ui->lineEdit_13->text()==""||ui->lineEdit_14->text()==""||
            ui->lineEdit_15->text()==""||ui->lineEdit_16->text()==""||ui->lineEdit_17->text()==""||ui->lineEdit_18->text()==""||
            ui->lineEdit_19->text()==""||ui->lineEdit_20->text()==""||ui->lineEdit->text()==""||
            ui->textEdit_3->toPlainText()=="")
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
            break;
        case 9:
            QMessageBox::information(0,"错误型号9","经费只能为数字");
            break;
        case 10:
            QMessageBox::information(0,"错误型号10","设备编号不能超过20位");
            break;
        case 11:
            QMessageBox::information(0,"错误型号11","除备注外，不允许存在空值属性");
            break;
        default:
            break;
    }


    //连接数据库并进行修改
    if(check == 0)
    {
        //if(tes.connectMysql())
        //{
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("equipments");
        model->setFilter("id = "+ ui->lineEdit_18->text());
        model->select();

        QString pose[] = {ui->lineEdit_11->text(),
                          ui->comboBox_4->currentText(),
                          ui->textEdit_3->toPlainText(),
                          ui->dateEdit_4->text(),
                          ui->dateEdit_5->text(),

                          ui->lineEdit_12->text(),
                          ui->lineEdit_13->text(),
                          ui->lineEdit_14->text(),
                          ui->lineEdit_15->text(),
                          ui->lineEdit_16->text(),
                          ui->comboBox_5->currentText(),

                          ui->lineEdit_17->text(),
                          ui->lineEdit_18->text(),
                          ui->lineEdit_19->text(),

                          ui->lineEdit_20->text(),
                          ui->dateEdit_6->text(),

                          ui->comboBox_6->currentText(),
                          ui->textEdit_4->toPlainText(),

                          ui->lineEdit->text(),
                         };

        //qDebug() << getID;
        int id = getID.toInt();
        QSqlQuery query;
        //修改数据库中的数据
        query.prepare("UPDATE equipment_information set name=?, types=?, basic_configuration=?,"
                       "date_of_purchase=?, date_of_manufacture=?, supplier=?, phone=?,"
                       "contact_person=?, cost=?, money_card_number=?, type_of_funding=?,"
                       "person_in_charge=?, manager=?, acceptance=?, user=?,"
                       "delivery_date=?, state_of_use=?, remarks=?, equipment_ID=? where id=?");
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
        QVariantList ids;
        ids << id;
        query.addBindValue(ids);

        //提示是否修改成功
        this->close();
        if(!query.execBatch()){
            QMessageBox::information(this,"提示","信息修改失败",QMessageBox::Yes);
        }
        else
            QMessageBox::information(0,"提示","修改成功");
        query.finish();
        //更新主界面的视图
        editModel->select();
        //}
    }
}
