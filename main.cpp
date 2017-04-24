#include "bookkeeping.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    createConnection();

    bookkeeping w;
    w.show();

    return app.exec();
}
