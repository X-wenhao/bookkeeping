#ifndef WISH_BOTTLE_H
#define WISH_BOTTLE_H

#include <QWidget>

namespace Ui {
class wish_bottle;
}

class wish_bottle : public QWidget
{
    Q_OBJECT

public:
    explicit wish_bottle(QWidget *parent = 0);
    ~wish_bottle();

private:
    Ui::wish_bottle *ui;
};

#endif // WISH_BOTTLE_H
