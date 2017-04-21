#include "wish_bottle.h"
#include "ui_wish_bottle.h"

wish_bottle::wish_bottle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wish_bottle)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec("select * from analyze");
    QSqlRecord record_analyze=query.record();

    set_info();

}

void wish_bottle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QSqlQuery query;
    query.exec("select * from analyze");

    int surplus=0;
    while(query.next())
    {
        int outcome=-query.record().value("outcome").toInt();
        int budget=query.record().value("budget").toInt();
        if(outcome<budget)
        {
            surplus+=budget-outcome;
        }
    }
    qDebug()<<"surplus1"<<surplus;
    query.exec("select * from wish");
    int count=0;
    while(query.next())
    {
        count++;
    }
    qDebug()<<"count"<<count;
    query.exec("select * from wish");
    for(int i=1;i<=count-3;i++)
    {
        query.next();
        surplus-=query.record().value("money").toInt();
        qDebug()<<"surplus2"<<surplus;
    }

    QColor color[2];
    color[0]=QColor(65,193,235);
    color[1]=QColor(249,250,252);

    for(int i=1;i<=3;i++)
    {
        int x=0;
        int y=0;
        switch(i)
        {
            case 1:
                x=ui->wish_1->x();
                y=ui->wish_1->y();
                break;
            case 2:
                x=ui->wish_2->x();
                y=ui->wish_2->y();
                break;
            case 3:
                x=ui->wish_3->x();
                y=ui->wish_3->y();
                break;
        }
        //painter1(ui->wish_1);
        if(query.next())
        {
            int money=query.record().value("money").toInt();
            qDebug()<<"money"<<money;
            if(money>surplus)
            {
                painter.setPen(color[0]);
                painter.setBrush(color[0]);
                painter.setRenderHint(QPainter::Antialiasing,true);
                painter.drawPie(x+60,y+270,90,90,0,360*16*double(surplus)/money);

                painter.setPen(color[1]);
                painter.setBrush(color[1]);
                painter.drawPie(x+70,y+280,70,70,0,360*16*double(surplus)/money);
                surplus=0;
            }
            else
            {
                painter.setPen(color[0]);
                painter.setBrush(color[0]);
                painter.setRenderHint(QPainter::Antialiasing,true);
                painter.drawPie(x+60,y+270,90,90,0,360*16*double(surplus)/money);

                painter.setPen(color[1]);
                painter.setBrush(color[1]);
                painter.drawPie(x+70,y+280,70,70,0,360*16*double(surplus)/money);
                surplus-=money;
            }

        }
        else
        {

        }
    }
}

void wish_bottle::set_info()
{
    QSqlQuery query;
    query.exec("select * from analyze");

    int surplus=0;
    while(query.next())
    {
        int outcome=-query.record().value("outcome").toInt();
        int budget=query.record().value("budget").toInt();
        if(outcome<budget)
        {
            surplus+=budget-outcome;
        }
    }

    query.exec("select * from wish");
    int count=0;
    while(query.next())
    {
        count++;
    }

    query.exec("select * from wish");
    for(int i=1;i<=count-3;i++)
    {
        query.next();
        surplus-=query.record().value("money").toInt();
        qDebug()<<"surplus2"<<surplus;
    }

    for(int i=1;i<=3;i++)
    {
        QLabel *label;
        QTextBrowser *browser;
        switch(i)
        {
            case 1:
                label=ui->wish_1_percent;
                browser=ui->textBrowser;
                break;
            case 2:
            label=ui->wish_2_percent;
            browser=ui->textBrowser_2;
            break;
            case 3:
            label=ui->wish_3_percent;
            browser=ui->textBrowser_3;
                break;
        }
        //painter1(ui->wish_1);
        if(query.next())
        {
            int money=query.record().value("money").toInt();
            qDebug()<<"money"<<money;
            if(money>surplus)
            {
                int percent=int(double(surplus)/money*100);
                label->setText(QString::number(percent,10)+"%");
                browser->setPlainText(query.record().value("wish").toString());
                surplus=0;
            }
            else
            {
                int percent=int(double(surplus)/money*100);
                label->setText(QString::number(percent,10)+"%");
                browser->setPlainText(query.record().value("wish").toString());
                surplus-=money;
            }

        }
        else
        {
            label->setText("0%");
        }
    }
}

wish_bottle::~wish_bottle()
{
    delete ui;
}
