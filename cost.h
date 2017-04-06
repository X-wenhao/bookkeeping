#ifndef COST_H
#define COST_H

#include <QWidget>

namespace Ui {
class cost;
}

class cost : public QWidget
{
    Q_OBJECT

public:
    explicit cost(QWidget *parent = 0);
    ~cost();

private:
    Ui::cost *ui;
};

#endif // COST_H
