#ifndef BOOKKEEPING_H
#define BOOKKEEPING_H

#include <QMainWindow>

namespace Ui {
class bookkeeping;
}

class bookkeeping : public QMainWindow
{
    Q_OBJECT

public:
    explicit bookkeeping(QWidget *parent = 0);
    ~bookkeeping();

private:
    Ui::bookkeeping *ui;
};

#endif // BOOKKEEPING_H
