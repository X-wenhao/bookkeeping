#include "cost.h"
#include "ui_cost.h"

cost::cost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cost)
{
    ui->setupUi(this);
    //QString background="background-image: url(:/page/material/page/cost_bar.png";
    //this->setStyleSheet("background-image: url(:/page/material/page/cost_bar.png");
}

cost::~cost()
{
    delete ui;
}

void cost::paintEvent(QPaintEvent *event)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }

void cost::setinfo(QString type,QString reason,int money)
{
    ui->cost_type->setText(type);
    //ui->cost_reason->setText(reason);
    QString set_icon="background-image: url(:/cost_icon/material/小图标/"
            +type
            +".png);";
    ui->cost_icon->setStyleSheet(set_icon);

    QString money_s;

    if(money<0)
    {
        money_s="支出:"+QString::number(-money,10);
        ui->cost_money->setStyleSheet("color:rgb(57,137,183);"
                                      "font: 14pt 华文新魏;");
    }
    else
    {
        money_s="收入:"+QString::number(money,10);
        ui->cost_money->setStyleSheet("color:rgb(221,147,111);"
                                      "font: 14pt 华文新魏;");
    }
    ui->cost_money->setText(money_s);


}
