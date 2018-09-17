#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //创建主窗口
    ui->setupUi(this);
    this->resize(QSize( 900, 600 ));
    widget = new QWidget;
    setCentralWidget(widget);

    layout = new QVBoxLayout;
    //创建搜索按钮
    buttonCancel = new QPushButton;
    buttonCancel->setText("关闭");
    buttonSearch = new QPushButton;
    buttonSearch->setText("确定");

    //创建搜索控件
    lineEdit = new QLineEdit;
    combobox = new QComboBox;
    createComboBOX();
    hlayout = new QHBoxLayout;
    hlayout->addWidget(combobox);
    hlayout->addWidget(lineEdit);
    hlayout->addWidget(buttonSearch);
    hlayout->addWidget(buttonCancel);

    //控件和槽函数的连接
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openTable()));
    connect(ui->actionPrint,SIGNAL(triggered()),this,SLOT(doPrint()));
    connect(ui->actionPrintPreview,SIGNAL(triggered()),this,SLOT(doPrintPreview()));
    connect(ui->actionPdf,SIGNAL(triggered()),this,SLOT(doCreatePdf()));
    connect(ui->actionCloseSystem, SIGNAL(triggered(bool)), this, SLOT(doCloseApplication()));
    connect(ui->actionDelete, SIGNAL(triggered(bool)), this, SLOT(doDelete()));
    connect(ui->actionHelp, SIGNAL(triggered(bool)), this, SLOT(doHelp()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveData()));
    connect(ui->actionSearch, SIGNAL(triggered(bool)), this, SLOT(displaySearch()));
    connect(buttonSearch, SIGNAL(clicked(bool)), this, SLOT(doSelect()));
    connect(ui->actionAdd, SIGNAL(triggered(bool)), this, SLOT(addData()));
    connect(buttonCancel, SIGNAL(clicked(bool)), this, SLOT(cancelSearch()));
    connect(ui->actionAlter, SIGNAL(triggered(bool)), this, SLOT(editData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打印
void MainWindow::doPrint()
{
    if(!isOpened) return;
    // 创建打印机对象
    QPrinter printer(QPrinter::HighResolution);
    // 创建打印对话框
    QPrintDialog dlg(&printer, this);

    // 如果在对话框中按下了打印按钮，则执行打印操作
    if (dlg.exec() == QDialog::Accepted) {
        printDocument(&printer);
    }
}


// 打印预览
void MainWindow::doPrintPreview()
{
    if(!isOpened) return;
    QPrinter printer(QPrinter::HighResolution);
    // 创建打印预览对话框
    QPrintPreviewDialog preview(&printer, this);
     // 当要生成预览页面时，发射paintRequested()信号
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printDocument(QPrinter*)));
    preview.exec();
}

//打印文档
void MainWindow::printDocument(QPrinter *printer)
{
    QString strStream,strTitle;
    QTextStream out(&strStream);
    strTitle="carman——feng";
    const int rowCount =view->model()->rowCount();
    const int columnCount =view->model()->columnCount();
    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Textml; charset=Windows-1251\">\n"
         <<  QString("<title>%1</title>\n").arg(strTitle)
          <<  "</head>\n"
              "<body bgcolor=#ffffff link=#5000A0>\n"
              "<table border=1 cellspacing=0 cellpadding=2>\n";
    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; ++column)
        if (!view->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(view->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    // data table
    for (int row = 0; row < rowCount; ++row)
    {
        out << "<tr>";
        for (int column = 0; column < columnCount; ++column)
        {
            if (!view->isColumnHidden(column)) {
                QString data = view->model()->data(view->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
            "</body>\n"
            "<ml>\n";
    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);
    document->print(printer);
}

// 生成PDF文件
void MainWindow::doCreatePdf()
{
    if(!isOpened) return;
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"),
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {

        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer;
        // 指定输出格式为pdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        printDocument(&printer);
    }
}

//关闭程序
void MainWindow::doCloseApplication()
{
    if (!(QMessageBox::information(this,tr("提示"),tr("确定要退出系统?"),tr("是"),tr("否"))))
    {
        qApp->exit(0);
    }
}

//创建主窗口上面显示的表格
void MainWindow::createTable()
{
    model = new QSqlTableModel;
    model->setTable("equipment_information");

    //设置表格的表头
    model->setHeaderData(1, Qt::Horizontal, "名称");
    model->setHeaderData(2, Qt::Horizontal, "类型");
    model->setHeaderData(3, Qt::Horizontal, "基本配置");
    model->setHeaderData(4, Qt::Horizontal, "购买日期");
    model->setHeaderData(5, Qt::Horizontal, "出厂日期");
    model->setHeaderData(6, Qt::Horizontal, "设备编号");
    model->setHeaderData(7, Qt::Horizontal, "供应商");
    model->setHeaderData(8, Qt::Horizontal, "电话");
    model->setHeaderData(9, Qt::Horizontal, "联系人");
    model->setHeaderData(10, Qt::Horizontal, "经费");
    model->setHeaderData(11, Qt::Horizontal, "经费卡号");
    model->setHeaderData(12, Qt::Horizontal, "经费类型");
    model->setHeaderData(13, Qt::Horizontal, "经费负责人");
    model->setHeaderData(14, Qt::Horizontal, "经办人");
    model->setHeaderData(15, Qt::Horizontal, "验收人");
    model->setHeaderData(16, Qt::Horizontal, "使用人");
    model->setHeaderData(17, Qt::Horizontal, "送货日期");
    model->setHeaderData(18, Qt::Horizontal, "使用状态");
    model->setHeaderData(19, Qt::Horizontal, "备注");

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    //设置表格的视图
    view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setColumnHidden(0, true);
    view->resizeColumnsToContents();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

//打开表格
void MainWindow::openTable()
{
    if(database_connect.isConnected == 0)
    {
        database_connect.show();
    }
    if(!isOpened && database_connect.isConnected ){
        //创建表格
        createTable();
        //对控件进行布局
        layout->addLayout(hlayout);
        layout->addWidget(view);
        layout->setMargin(0);
        widget->setLayout(layout);
        isOpened = 1;
        buttonCancel->hide();
        buttonSearch->hide();
        lineEdit->hide();
        combobox->hide();
    }
}

//删除记录
void MainWindow::doDelete()
{
    if(!isOpened) return;
    int curRow = view->currentIndex().row();
    //获取选中的行
    if(curRow < 0) {
        QMessageBox::information(NULL, "说明", "请选择一项进行删除");
        return;
    }
    model->removeRow(curRow);
    //删除该行
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定""删除当前行吗？"),
                                   QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        model->revertAll(); //如果不删除，则撤销
    }
    else
        model->submitAll(); //否则提交，在数据库中删除该行
}

//说明文字
void MainWindow::doHelp()
{
    QMessageBox::about(NULL, "说明","实验室设备和材料的出入库管理系统\n©Herbert_Hu");
}

//保存
void MainWindow::saveData()
{
    if(!isOpened) return;
    model->setFilter("");
    model->select();
    QMessageBox::about(NULL, "提示", "数据已保存到数据库");
}

//创建下拉选框
void MainWindow::createComboBOX()
{
    combobox->addItem(QWidget::tr("名称"));
    combobox->addItem(QWidget::tr("类型"));
    combobox->addItem(QWidget::tr("基本配置"));
    combobox->addItem(QWidget::tr("购买日期"));
    combobox->addItem(QWidget::tr("出厂日期"));
    combobox->addItem(QWidget::tr("设备编号"));
    combobox->addItem(QWidget::tr("供应商"));
    combobox->addItem(QWidget::tr("电话"));
    combobox->addItem(QWidget::tr("联系人"));
    combobox->addItem(QWidget::tr("经费"));
    combobox->addItem(QWidget::tr("经费卡号"));
    combobox->addItem(QWidget::tr("经费类型"));
    combobox->addItem(QWidget::tr("经费负责人"));
    combobox->addItem(QWidget::tr("经办人"));
    combobox->addItem(QWidget::tr("验收人"));
    combobox->addItem(QWidget::tr("使用人"));
    combobox->addItem(QWidget::tr("送货日期"));
    combobox->addItem(QWidget::tr("使用状态"));
    combobox->addItem(QWidget::tr("备注"));
}

//显示搜索按钮
void MainWindow::displaySearch()
{
    if(!isOpened) return;
    if(!isSelect){
        buttonCancel->show();
        buttonSearch->show();
        lineEdit->show();
        combobox->show();
        isSelect = 1;
    }
 }

//执行搜索
void MainWindow::doSelect()
{
    QString name = lineEdit->text();
    int pose = combobox->currentIndex();

    if(name.isEmpty())
    {
        model->setFilter("");
    }
    else
    {
        switch (pose)
        {
            case 0: model->setFilter(QString("name LIKE '%%1%'").arg(name)); //根据名称进行筛选
                break;
            case 1: model->setFilter(QString("types LIKE '%%1%'").arg(name)); //根据类型进行筛选
                break;
            case 2: model->setFilter(QString("basic_configuration LIKE '%%1%'").arg(name)); //根据基本配置进行筛选
                break;
            case 3: model->setFilter(QString("date_of_purchase LIKE '%%1%'").arg(name)); //根据购买日期进行筛选
                break;
            case 4: model->setFilter(QString("date_of_manufacture LIKE '%%1%'").arg(name)); //根据出厂日期进行筛选
                break;
            case 5: model->setFilter(QString("equipment_ID LIKE '%%1%'").arg(name)); //根据设备编号进行筛选
                break;
            case 6: model->setFilter(QString("supplier LIKE '%%1%'").arg(name)); //根据供应商进行筛选
                break;
            case 7: model->setFilter(QString("phone LIKE '%%1%'").arg(name)); //根据电话进行筛选
                break;
            case 8: model->setFilter(QString("contact_person LIKE '%%1%'").arg(name)); //根据联系人进行筛选
                break;
            case 9: model->setFilter(QString("cost LIKE '%%1%'").arg(name)); //根据经费进行筛选
                break;
            case 10: model->setFilter(QString("money_card_number LIKE '%%1%'").arg(name)); //根据经费卡号进行筛选
                break;
            case 11: model->setFilter(QString("type_of_funding LIKE '%%1%'").arg(name)); //根据经费类型进行筛选
                break;
            case 12: model->setFilter(QString("person_in_charge LIKE '%%1%'").arg(name)); //根据经费负责人进行筛选
                break;
            case 13: model->setFilter(QString("manager LIKE '%%1%'").arg(name)); //根据经办人进行筛选
                break;
            case 14: model->setFilter(QString("acceptance LIKE '%%1%'").arg(name)); //根据验收人进行筛选
                break;
            case 15: model->setFilter(QString("user LIKE '%%1%'").arg(name)); //根据使用人进行筛选
                break;
            case 16: model->setFilter(QString("delivery_date LIKE '%%1%'").arg(name)); //根据送货日期进行筛选
                break;
            case 17: model->setFilter(QString("state_of_use LIKE '%%1%'").arg(name)); //根据使用状态进行筛选
                break;
            case 18: model->setFilter(QString("remarks LIKE '%%1%'").arg(name)); //根据备注进行筛选
                break;
            default:
                break;
        }
    }

    if(model->select() && model->rowCount() != 0)
    {
        model->select(); //显示结果
    }
    else
    {
        model->setFilter("");
        QMessageBox::critical(0,"查找失败","很抱歉，没有符合条件的数据存在于数据库中");
    }

}

//插入记录
void MainWindow::addData()
{
    if(!isOpened) return;
    Add.show();
    Add.exec();
    model->select();
}

//关闭搜索按钮
void MainWindow::cancelSearch()
{
    buttonCancel->hide();
    buttonSearch->hide();
    lineEdit->hide();
    combobox->hide();
    isSelect = 0;
    model->setFilter("");
   // model->select();
}

//编辑数据
void MainWindow::editData()
{
    //修改提交
        if(!isOpened) return;
        int rowNum = view->currentIndex().row(); //获得当前行的ID；
        if(rowNum < 0) {
            QMessageBox::information(NULL, "说明", "请选择一项进行编辑");
            return;
        }
        QSqlRecord record = model->record(rowNum);
        int id = record.value("id").toInt();
        //qDebug()<<rowNum << " id " << id;
        QString text =  QString::number(id, 10);
        //将ID传送给Dialog界面
        QSqlTableModel* windowModel = model;
        Edit.setWindowModel(windowModel);
        Edit.getMyid(text);
        Edit.change();
        Edit.show();
        //model->select();
}
