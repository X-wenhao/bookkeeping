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
