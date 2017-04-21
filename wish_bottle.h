#ifndef WISH_BOTTLE_H
#define WISH_BOTTLE_H

#include <QWidget>
#include <QPainter>
#include "database.h"
#include <QPaintEvent>

namespace Ui {
class wish_bottle;
}

class wish_bottle : public QWidget
{
    Q_OBJECT

public:
    explicit wish_bottle(QWidget *parent = 0);
    ~wish_bottle();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::wish_bottle *ui;
    void set_info();
};

#endif // WISH_BOTTLE_H
