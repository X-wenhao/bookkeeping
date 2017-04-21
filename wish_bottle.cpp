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
        QWidget *label_back;
        QLabel *label_in;
        switch(i)
        {
            case 1:
                label=ui->wish_1_percent;
                browser=ui->textBrowser;
                label_back=ui->widget_1;
                label_in=ui->label_2;
                break;
            case 2:
            label=ui->wish_2_percent;
            browser=ui->textBrowser_2;
            label_back=ui->widget_2;
            label_in=ui->label_6;
            break;
            case 3:
            label=ui->wish_3_percent;
            browser=ui->textBrowser_3;
            label_back=ui->widget_3;
            label_in=ui->label_7;
            break;
        }
        //painter1(ui->wish_1);
        if(query.next())
        {
            int money=query.record().value("money").toInt();
            qDebug()<<"money123"<<money;
            if(money>surplus)
            {
                int percent=int(double(surplus)/money*100);
                label->setText(QString::number(percent,10)+"%");
                label->raise();
                browser->setPlainText(query.record().value("wish").toString());

                label_back->setStyleSheet("background-image: url(:/WishBottle/material/wish_bottle/瓶子.png);");
                label_in->setStyleSheet("background-image: url(:/WishBottle/material/wish_bottle/stars.png);"
                                        "background-color: rgba(255, 255, 255, 0);");
                int x=label_in->x();
                int y=label_in->y();
                int width=label_in->width();
                int height=label_in->height();
                y+=(1-double(surplus)/money)*height;
                qDebug()<<y;
                height*=double(surplus)/money;
                qDebug()<<height;
                label_in->setGeometry(x,y,height,width);
                if(label_in->isHidden())
                {
                    label_in->show();
                }
                surplus=0;
            }
            else
            {
                int percent=int(double(surplus)/money*100);
                label->setText(QString::number(percent,10)+"%");
                label->raise();
                browser->setPlainText(query.record().value("wish").toString());
                label_back->setStyleSheet("background-image: url(:/WishBottle/material/wish_bottle/瓶子.png);");
                label_in->setStyleSheet("background-image: url(:/WishBottle/material/wish_bottle/stars.png);"
                                        "background-color: rgba(255, 255, 255, 0);");
                if(label_in->isHidden())
                {
                    label_in->show();
                }

                surplus-=money;
            }

        }
        else
        {
            label->setText(" ");

            label_back->setStyleSheet("background-image: url(:/WishBottle/material/wish_bottle/待添加.png);");
            if(label_in->isVisible())
            {
                label_in->hide();
            }
        }
    }
}

wish_bottle::~wish_bottle()
{
    delete ui;
}
