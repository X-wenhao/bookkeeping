#include "bookkeeping.h"
#include "ui_bookkeeping.h"

bookkeeping::bookkeeping(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bookkeeping)
{
    ui->setupUi(this);
    set_validator();
    //this->setWindowFlags(Qt::FramelessWindowHint);

    //获取预算
    QSqlQuery query;
    //query.exec("select * from user");
    //query.next();
    //int money =query.record().value("money").toInt();
    //QString username=query.record().value("name").toString();
    //qDebug()<<money;
    //ui->showmoney->setText(QString::number(money,10));
    //ui->username->setText(username);

    //获取收入与支出
    query.exec("select * from cost");
    int income=0;
    int cost=0;
    while(query.next())
    {
        int temp=query.record().value("money").toInt();
        if(temp>0)
        {
            income+=temp;
        }
        else
        {
            cost+=temp;
        }
    }
    ui->cost->setText(QString::number(-cost,10));
    ui->cost_2->setText(QString::number(-cost,10));
    ui->income->setText(QString::number(income,10));

    //设置下拉菜单
    QDateTime time=QDateTime::currentDateTime();
    QString current_year=time.toString("yyyy");
    for(int i=1;i<=12;i++)
    {
        ui->cob_year->addItem(QString::number(i+current_year.toInt()-5,10));
        ui->cob_mon->addItem(QString::number(i,10));
    }
    ui->cob_year->setCurrentText(current_year);
    ui->cob_mon->setCurrentText(time.toString("M"));

    //设置滚动
    ui->scrollArea->setWidget(ui->widget_show_cost);

    //init page_write
    ui->write_year->setText(current_year);
    ui->write_month->setText(time.toString("M"));
    ui->write_day->setText(time.toString(time.toString("d")));
    ui->write_radio_income->setChecked(true);
    ui->write_radio_out->setChecked(true);

    //register page_2 and page_3
    page_2=new analyze(ui->centralWidget);
    page_2->hide();

    page_3=new wish_bottle(ui->centralWidget);
    page_3->hide();

    //set budget
    query.prepare("select budget from analyze where time=:time");
    query.bindValue(":time",ui->cob_year->currentText()+"-"+ui->cob_mon->currentText());
    query.exec();
    query.next();
    ui->showmoney->setText(query.record().value("budget").toString());

    init_button_group();
    init_widget_show_cost(0);
    ui->widget_show_cost->setStyleSheet("background-color: rgb(240, 241, 242)");

}
bookkeeping::~bookkeeping()
{
    delete ui;
}

void bookkeeping::on_editmoney_clicked()
{
    QSqlQuery query;
    query.prepare("select * from analyze where time=:time");
    QString time=ui->cob_year->currentText()+"-"+ui->cob_year->currentText();
    query.bindValue(":time",time);
    query.exec();
    if(query.next())
    {
        query.prepare("update analyze set budget=:budget where time=:time");
        query.bindValue(":budget",ui->editmoney->text().toInt());
        query.bindValue(":time",time);
        query.exec();
    }
    else
    {
        query.prepare("insert into analyze(time,income,outcome,clothe,food ,out,other,budget)"
                      "values(:time,0,0,0,0,0,0,:budget)");
        query.bindValue(":budget",ui->editmoney->text().toInt());
        query.bindValue(":time",time);
        query.exec();
    }
}


void bookkeeping::on_write_new_cost_clicked()
{
    //ui->cost->setText(QString("12"));
    if(ui->write_year->text().isEmpty()||ui->write_reason->toPlainText().isEmpty())
    {
        QMessageBox::critical(0,"Cannot submit!",
                              "please complish!",QMessageBox::Cancel);
    }
    else
    {
        int money=ui->write_money->text().toInt();
        if(write_type_group.checkedButton()->text()=="支出")
        {
            money=-money;
            qDebug()<<money;
        }
        QString kind=write_kind_group.checkedButton()->text();
        QString time=ui->write_year->text()+"-"
                +ui->write_month->text();
        QString reason=ui->write_reason->toPlainText();
        QSqlQuery query;
        query.prepare("insert into cost(type,money,reason,time)"
                      "values(:type,:money,:reason,:time)");
        query.bindValue(":type",kind);
        query.bindValue(":money",money);
        query.bindValue(":reason",reason);
        query.bindValue(":time",time+"-"
                        +ui->write_day->text());
        query.exec();
        //update analyze
        query.prepare("select * from analyze where time=:time");
        query.bindValue(":time",ui->write_year->text()+"-"+ui->write_month->text());
        query.exec();
        if(!query.next())
        {
            query.prepare("insert into analyze(time,income,outcome,clothe,food ,out,other,budget)"
                          "values(:time,0,0,0,0,0,0,:budget)");
            query.bindValue(":budget",ui->editmoney->text().toInt());
            query.bindValue(":time",ui->write_year->text()+"-"+ui->write_month->text());
            query.exec();
            query.prepare("select * from analyze where time=:time");
            query.bindValue(":time",ui->write_year->text()+"-"+ui->write_month->text());
            query.exec();
            query.next();
        }
        QSqlRecord record=query.record();

        if(money<0)
        {
            query.prepare("update analyze set outcome=:money where time=:time");
            query.bindValue(":money",money+record.value("outcome").toInt());
        }
        else
        {
            query.prepare("update analyze set income=:money where time=:time");
            query.bindValue(":money",money+record.value("income").toInt());
        }
        query.bindValue(":time",ui->write_year->text()+"-"+ui->write_month->text());
        qDebug()<<ui->write_year->text()+"-"+ui->write_month->text()<<"金额"<<money+record.value("outcome").toInt();
        query.exec();
        if(money<0)
        {
            QString conp="other";
            if(kind=="服装")
            {
                conp="clothe";
            }
            else if(kind=="餐饮"||kind=="酒水"||kind=="零食")
            {
                conp="food";
            }
            else if(kind=="出行"||kind=="旅行")
            {
                conp="out";
            }
            query.prepare("update analyze set "+conp+"=:money where time=:time");
            query.bindValue(":money",money+record.value(conp).toInt());
            query.bindValue(":time",ui->write_year->text()+"-"+ui->write_month->text());
            query.exec();
        }

        ui->write_money->clear();
        ui->write_reason->clear();
        ui->write_radio_income->setChecked(true);
        ui->write_radio_out->setChecked(true);

        QMessageBox::information(NULL,"Infrmation","Submit successfully");
    }
}

void bookkeeping::on_to_page_write_clicked()
{
    //test

    //QSqlQuery query;
    //query.exec("insert into cost(type,money,reason,time)values('出行',-140,'无','2017-4-6')");
    ui->stackedWidget->setCurrentWidget(ui->page_write);
}


void bookkeeping::init_widget_show_cost(int status)
{
    if(status==1)
    {
        QObjectList items=ui->widget_show_cost->children();
        int num=items.count();
        for(int i=0;i<num;i++)
        {
            if(items[i]->objectName()=="to_page_write")
            {
                continue;
            }
            delete items[i];
        }
    }
    QSqlQuery query;
    QString query_time=ui->cob_year->currentText()+"-"+ui->cob_mon->currentText()+"-";
    int y=0;
    for(int i=31;i>0;i--)
    {
        query.prepare("select * from cost where time=:time");
        query.bindValue(":time",query_time+QString::number(i,10));
        query.exec();
        //qDebug()<<query_time+QString::number(i,10);
        if(query.next())
        {
            cost_time *cost_time1=new cost_time(ui->widget_show_cost);
            cost_time1->move(0,y);
            y+=cost_time1->height();
            cost_time1->show();
            int sum_money=0;
            do
            {
                cost *cost1=new cost(ui->widget_show_cost);
                //ui->verticalLayout->addWidget(cost1);
                cost1->move(0,y);
                y+=cost1->height();
                int tempmoney=query.record().value("money").toInt();
                if(tempmoney<0)
                {
                    sum_money+=tempmoney;
                }
                QString type=query.record().value("type").toString();
                QString reason=query.record().value("reason").toString();
                QString money=query.record().value("money").toString();
                if(money.toInt()<0)
                {
                    money="支出："+money+"元";
                }
                else
                {
                    money="收入："+money+"元";
                }
                cost1->setinfo(type,reason,money);
                cost1->show();
            }while(query.next());
            QString month=ui->cob_mon->currentText()+"月"+QString::number(i,10)+"日";
            QString week="星期一";
            QString money="支出："+QString::number(sum_money,10);
            cost_time1->setinfo(month,week,money);
        }
    }

}

void bookkeeping::on_cob_year_currentTextChanged(const QString &arg1)
{
    init_widget_show_cost(1);
}

void bookkeeping::on_cob_mon_currentTextChanged(const QString &arg1)
{
    init_widget_show_cost(1);
    //qDebug()<<ui->cob_mon->currentText();
}

void bookkeeping::on_back_to_page_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    init_widget_show_cost(1);
}

void bookkeeping::set_validator()
{
    //设置page
    QIntValidator *validator_for_showmoney=new QIntValidator(0,1000000,this);
    ui->showmoney->setValidator(validator_for_showmoney);

    //设置page_write
    QIntValidator *validator_for_write_year=new QIntValidator(2000,2020,this);
    ui->write_year->setValidator(validator_for_write_year);
    QIntValidator *validator_for_write_month=new QIntValidator(1,12,this);
    ui->write_month->setValidator(validator_for_write_month);
    QIntValidator *validator_for_write_day=new QIntValidator(1,31,this);
    ui->write_day->setValidator(validator_for_write_day);
    QIntValidator *validator_for_write_money=new QIntValidator(0,10000000,this);
    ui->write_money->setValidator(validator_for_write_money);
}


void bookkeeping::on_write_month_editingFinished()
{
    if(ui->write_month->text().isEmpty())
    {
        QIntValidator *validator_for_write_day=new QIntValidator(1,31,this);
        ui->write_day->setValidator(validator_for_write_day);
    }
    else
    {
        QIntValidator *validator_for_write_day=new QIntValidator(1,31,this);
        ui->write_day->setValidator(validator_for_write_day);
    }
}

void bookkeeping::init_button_group()
{
    //set group
    write_type_group.addButton(ui->write_radio_income);
    write_type_group.addButton(ui->write_radio_outcome);

    write_kind_group.addButton(ui->write_radio_out);
    write_kind_group.addButton(ui->radioButton_4);
    write_kind_group.addButton(ui->radioButton_5);
    write_kind_group.addButton(ui->radioButton_6);
    write_kind_group.addButton(ui->radioButton_7);
    write_kind_group.addButton(ui->radioButton_8);
    write_kind_group.addButton(ui->radioButton_9);
    write_kind_group.addButton(ui->radioButton_10);
    write_kind_group.addButton(ui->radioButton_11);
    write_kind_group.addButton(ui->radioButton_12);
    write_kind_group.addButton(ui->radioButton_13);
    write_kind_group.addButton(ui->radioButton_14);
    write_kind_group.addButton(ui->radioButton_15);
    write_kind_group.addButton(ui->radioButton_16);
    write_kind_group.addButton(ui->radioButton_17);
    write_kind_group.addButton(ui->radioButton_18);
    write_kind_group.addButton(ui->radioButton_19);
    write_kind_group.addButton(ui->radioButton_20);
    write_kind_group.addButton(ui->radioButton_21);
    write_kind_group.addButton(ui->radioButton_22);
    write_kind_group.addButton(ui->radioButton_23);
}

void bookkeeping::on_pushButton_2_clicked()
{
    if(ui->stackedWidget->isVisibleTo(this))
    {
        ui->stackedWidget->hide();
    }
    if(page_3->isVisibleTo(this))
    {
        page_3->hide();
    }
    page_2->move(228,0);
    page_2->show();

}

void bookkeeping::on_pushButton_clicked()
{
    page_2->hide();
    page_3->hide();

    ui->stackedWidget->show();
}

void bookkeeping::on_pushButton_3_clicked()
{
    ui->stackedWidget->hide();
    page_2->hide();

    page_3->show();
    page_3->move(228,0);
}
