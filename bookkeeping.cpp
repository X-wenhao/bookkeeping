#include "bookkeeping.h"
#include "ui_bookkeeping.h"
#include "database.h"
#include <QIntValidator>
bookkeeping::bookkeeping(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bookkeeping)
{
    ui->setupUi(this);

    QIntValidator *validator_for_showmoney=new QIntValidator(0,1000000,this);
    ui->showmoney->setValidator(validator_for_showmoney);

    QSqlQuery query;
    query.exec("select * from user");
    query.next();
    int money =query.record().value("money").toInt();
    QString username=query.record().value("name").toString();
    qDebug()<<money;
    ui->showmoney->setText(QString::number(money,10));
    ui->username->setText(username);

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
