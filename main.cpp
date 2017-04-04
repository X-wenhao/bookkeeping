#include "bookkeeping.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bookkeeping w;
    w.show();

    return a.exec();
}
