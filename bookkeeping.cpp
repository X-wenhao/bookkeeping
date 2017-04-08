#include "bookkeeping.h"
#include "ui_bookkeeping.h"

bookkeeping::bookkeeping(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bookkeeping)
{
    ui->setupUi(this);

    //获取预算与用户名
    QSqlQuery query;
    query.exec("select * from user");
    query.next();
    int money =query.record().value("money").toInt();
    QString username=query.record().value("name").toString();
    qDebug()<<money;
    ui->showmoney->setText(QString::number(money,10));
    ui->username->setText(username);

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

    init_widget_show_cost(0);

}
bookkeeping::~bookkeeping()
{
    delete ui;
}

void bookkeeping::on_editmoney_clicked()
{
    QSqlQuery query;
    query.prepare("update user set money=:money where id=1");
    query.bindValue(":money",ui->showmoney->text().toInt());
    query.exec();
}


void bookkeeping::on_write_new_cost_clicked()
{
    //ui->cost->setText(QString("12"));

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
        qDebug()<<query_time+QString::number(i,10);
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
                cost1->move(0,y);
                y+=cost1->height();
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
    qDebug()<<ui->cob_mon->currentText();
}

void bookkeeping::on_back_to_page_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void bookkeeping::set_validator()
{
    //设置page
    QIntValidator *validator_for_showmoney=new QIntValidator(0,1000000,this);
    ui->showmoney->setValidator(validator_for_showmoney);

    //设置page_write
