#ifndef COST_TIME_H
#define COST_TIME_H

#include <QWidget>

namespace Ui {
class cost_time;
}

class cost_time : public QWidget
{
    Q_OBJECT

public:
    explicit cost_time(QWidget *parent = 0);
    ~cost_time();
    void setinfo(QString month,QString week,QString money);
private:
    Ui::cost_time *ui;
};

#endif // COST_TIME_H
