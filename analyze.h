#ifndef ANALYZE_H
#define ANALYZE_H

#include <QWidget>
#include <QDateTime>
#include <QPainter>
#include "database.h"
#include <QPaintEvent>
namespace Ui {
class analyze;
}

class analyze : public QWidget
{
    Q_OBJECT

public:
    explicit analyze(QWidget *parent = 0);
    ~analyze();

private:
    Ui::analyze *ui;
    void init_labels(int status);
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_two_month_currentTextChanged(const QString &arg1);
    void on_two_exchange_status_clicked();
};

#endif // ANALYZE_H
