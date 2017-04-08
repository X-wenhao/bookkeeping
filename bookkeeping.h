#ifndef BOOKKEEPING_H
#define BOOKKEEPING_H

#include <QMainWindow>
#include "database.h"
#include <QIntValidator>
#include "cost.h"
#include "cost_time.h"

namespace Ui {
class bookkeeping;
}

class bookkeeping : public QMainWindow
{
    Q_OBJECT

public:
    explicit bookkeeping(QWidget *parent = 0);
    ~bookkeeping();

private slots:
    void on_editmoney_clicked();

    void on_write_new_cost_clicked();

    void on_to_page_write_clicked();

    void on_cob_year_currentTextChanged(const QString &arg1);

    void on_cob_mon_currentTextChanged(const QString &arg1);

    void on_back_to_page_clicked();

private:
    Ui::bookkeeping *ui;
    void set_validator();
    void init_widget_show_cost(int status);
};

#endif // BOOKKEEPING_H
