#ifndef WISH_BOTTLE_H
#define WISH_BOTTLE_H

#include <QWidget>
#include <QPainter>
#include "database.h"
#include <QPaintEvent>
#include <QPalette>
#include <QIntValidator>
#include <QMessageBox>
#include <QTextEdit>
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

private slots:
    void on_pushButton_4_clicked();

    void on_add_wish_clicked();

private:
    Ui::wish_bottle *ui;
    void set_info();
    QTextEdit *text;
};

#endif // WISH_BOTTLE_H
