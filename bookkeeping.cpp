#include "bookkeeping.h"
#include "ui_bookkeeping.h"

bookkeeping::bookkeeping(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bookkeeping)
{
    ui->setupUi(this);
}

bookkeeping::~bookkeeping()
{
    delete ui;
}
