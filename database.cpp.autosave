#include "database.h"

bool createConnection(void)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bookkeeping.db");
    if(!db.open())
    {
        QMessageBox::critical(0,"Cannot open database",
                              "Unable to eatablish a database connection.",QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    query.exec("create table user(id INTEGER PRIMARY KEY AUTOINCREMENT, name varchar, password varchar, money float,begin_month int)");

    query.exec("create table cost(id INTEGER PRIMARY KEY AUTOINCREMENT, type varchar, money float,reason varchar,time text)");

    query.exec("create table analyze(id INTEGER PRIMARY KEY AUTOINCREMENT,time text,income float,"
               "outcome float,clothe float,food float,out float,other float,budget float)");

    query.exec("create table wish(id INTEGER PRIMARY KEY AUTOINCREMENT, money float,wish text,status int,surplus float)");

    return true;

}
