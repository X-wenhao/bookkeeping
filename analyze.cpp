#include "analyze.h"
#include "ui_analyze.h"

analyze::analyze(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analyze)
{
    ui->setupUi(this);

    //设置下拉菜单
    QDateTime time=QDateTime::currentDateTime();
    QString current_year=time.toString("yyyy");
    for(int i=1;i<=12;i++)
    {
        ui->two_year->addItem(QString::number(i+current_year.toInt()-5,10));
        ui->two_month->addItem(QString::number(i,10));
    }
    ui->two_year->setCurrentText(current_year);
    ui->two_month->setCurrentText(time.toString("M"));

    init_labels(0);
}

analyze::~analyze()
{
    delete ui;
}


void analyze::paintEvent(QPaintEvent *event)
{
    QSqlQuery query;
    int data_pre[7][6]={0};
    for(int i=6;i>=0;i--)
    {
        query.prepare("select * from analyze where time=:time");
        int month=ui->two_month->currentText().toInt()-6+i;
        if(month<=0)
        {
            month+=12;
        }
        query.bindValue(":time",ui->two_year->currentText()+"-"+QString::number(month,10));
        query.exec();
        if(query.next())
        {
            data_pre[i][0]=query.record().value("income").toInt();
            data_pre[i][1]=-query.record().value("outcome").toInt();
            data_pre[i][2]=-query.record().value("clothe").toInt();
            data_pre[i][3]=-query.record().value("food").toInt();

            data_pre[i][4]=-query.record().value("out").toInt();
            data_pre[i][5]=-query.record().value("other").toInt();
            qDebug()<<data_pre[i][1];
        }
    }

    QPainter painter(this);

    //first
    int x=ui->two_widget_first->x();
    int y=ui->two_widget_first->y();
    qDebug()<<x<<endl<<y;
    int height=ui->two_widget_first->height();
    int width=ui->two_widget_first->width();

    painter.setPen(QColor(0,160,230));
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawLine(QPointF(x+20,y+height-60),QPointF(x+width-20,y+height-60));
    // 设置字体：微软雅黑、点大小
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(20);
    painter.setFont(font);
    int j=1;
    if(ui->two_exchange_status->isChecked())
    {
        j=0;
    }
    for(int i=0;i<6;i++)
    {
        painter.drawLine(QPointF(x+10+60*i,y+height-data_pre[i][j]/10-150),QPointF(x+10+60*(i+1),y+height-data_pre[i+1][j]/10-150));
    }



}

void analyze::on_two_month_currentTextChanged(const QString &arg1)
{
    update();
    init_labels(1);
}

void analyze::init_labels(int status)
{
    QSqlQuery query;
    int data_pre[7][6]={0};
    for(int i=6;i>=0;i--)
    {
        query.prepare("select * from analyze where time=:time");
        int month=ui->two_month->currentText().toInt()-6+i;
        if(month<=0)
        {
            month+=12;
        }
        query.bindValue(":time",ui->two_year->currentText()+"-"+QString::number(month,10));
        query.exec();
        if(query.next())
        {
            data_pre[i][0]=query.record().value("income").toInt();
            data_pre[i][1]=-query.record().value("outcome").toInt();
            data_pre[i][2]=-query.record().value("clothe").toInt();
            data_pre[i][3]=-query.record().value("food").toInt();

            data_pre[i][4]=-query.record().value("out").toInt();
            data_pre[i][5]=-query.record().value("other").toInt();
            qDebug()<<data_pre[i][1];
        }
    }

    int x=ui->two_widget_first->x();
    int y=ui->two_widget_first->y();
    qDebug()<<x<<endl<<y;
    int height=ui->two_widget_first->height();
    int width=ui->two_widget_first->width();

    int j=1;
    if(ui->two_exchange_status->isChecked())
    {
        j=0;
    }

    if(status)
    {
        QObjectList items=ui->two_widget_first->children();
        int num=items.count();
        for(int i=0;i<num;i++)
        {
            delete items[i];
        }
    }

    for(int i=0;i<7;i++)
    {

        QLabel *temp1=new QLabel(ui->two_widget_first);
        QLabel *temp2=new QLabel(ui->two_widget_first);

        temp1->setText(QString::number(data_pre[i][j],10));
        temp1->move(10+60*i,height-data_pre[i][j]/20-150);
        temp1->show();

        int month=ui->two_month->currentText().toInt()-6+i;
        if(month<=0)
        {
            month+=12;
        }
        temp2->setText(QString::number(month,10));
        temp2->move(10+60*i,height-35);
        temp2->show();
    }

}
