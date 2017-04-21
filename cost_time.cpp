#include "cost_time.h"
#include "ui_cost_time.h"

cost_time::cost_time(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cost_time)
{
    ui->setupUi(this);
}

cost_time::~cost_time()
{
    delete ui;
}

void cost_time::setinfo(QString month,QString week,QString money)
{
    ui->costtime_month->setText(month);
    //ui->cost_time_week->setText(week);
    ui->cost_time_money->setText(money);
}
