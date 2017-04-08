#include "cost.h"
#include "ui_cost.h"

cost::cost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cost)
{
    ui->setupUi(this);
}

cost::~cost()
{
    delete ui;
}

void cost::setinfo(QString type,QString reason,QString money)
{
    ui->cost_icon->setText(type);
    ui->cost_reason->setText(reason);
    ui->cost_money->setText(money);
}
