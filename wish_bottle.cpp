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

}

wish_bottle::~wish_bottle()
{
    delete ui;
}