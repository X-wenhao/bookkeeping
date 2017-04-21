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

void cost::setinfo(QString type,QString reason,QString money)
{
    ui->cost_type->setText(type);
    //ui->cost_reason->setText(reason);
    ui->cost_money->setText(money);
}
