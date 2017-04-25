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
    ui->two_icon_exchange->setStyleSheet("background-image: url(:/page/material/支出/图层 1.png);");

    init_labels(0);
}

analyze::~analyze()
{
    delete ui;
}


void analyze::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    p.setBrush(QColor(255,255,255));
    p.drawRect(0,0,792,768);

    QSqlQuery query;
    int data_pre[7][6]={0};
    int max_income=0;
    int max_outcome=0;
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
            qDebug()<<i<<":"<<data_pre[i][1];
        }
        if(max_income<data_pre[i][0])
        {
            max_income=data_pre[i][0];
        }
        if(max_outcome<data_pre[i][1])
        {
            max_outcome=data_pre[i][1];
        }

    }

    QPainter painter(this);

    //first
    int x=ui->two_widget_first->x();
    int y=ui->two_widget_first->y();
    int height=ui->two_widget_first->height();
    int width=ui->two_widget_first->width();

    painter.setPen(QColor(0,160,230));
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawLine(QPointF(x+40,y+height-60),QPointF(x+width-200,y+height-60));

    int j=1;
    int max=max_outcome;
    if(ui->two_exchange_status->isChecked())
    {
        j=0;
        max=max_income;
        painter.setPen(QColor(229,174,143));
    }
    for(int i=0;i<6;i++)
    {
        painter.drawLine(QPointF(x+50+60*i,y+height-80-double(data_pre[i][j])/max*(height-100)),
                         QPointF(x+50+60*(i+1),y+height-80-double(data_pre[i+1][j])/max*(height-100)));

        qDebug()<<"point"<<y+height-80-data_pre[i+1][j]/max*(height-80);

    }

    x=ui->two_widget_second->x();
    y=ui->two_widget_second->y();
    height=ui->two_widget_second->height();
    width=ui->two_widget_second->width();

    QColor color[4];
    color[0]=QColor(132,197,235);
    color[1]=QColor(93,171,233);
    color[2]=QColor(165,208,238);
    color[3]=QColor(45,135,200);

    if(data_pre[6][1]!=0)
    {
        for(int i=1;i<5;i++)
        {
            painter.setPen(color[i-1]);
            painter.setBrush(color[i-1]);
            int begin=0;
            if(i!=1)
            {
                begin=360*16*double(data_pre[6][i])/data_pre[6][1];
                qDebug()<<begin;
            }
            painter.drawPie(90+30,y+30,150,150,begin,360*16*double(data_pre[6][i+1])/data_pre[6][1]);
            painter.drawPie(30+30,y+40*i,20,20,0,360*16);
        }
    }
    for(int i=6;i>=0;i--)
    {
        int total=double(data_pre[i][1])/max_outcome*(height-100);
        qDebug()<<"total:"<<total;
        if(data_pre[i][1]!=0)
        {
            int begin=y+height-100;
            for(int j=1;j<5;j++)
            {
                painter.setPen(color[j-1]);
                painter.setBrush(color[j-1]);
                begin-=double(data_pre[i][j+1])/data_pre[i][1]*total;
                qDebug()<<"up"<<data_pre[i][j+1];
                qDebug()<<"begin:"<<begin;
                qDebug()<<"dre:"<<data_pre[i][j+1]/data_pre[i][1]*total;
                painter.drawRect(x+260+60*i,begin, 30,double(data_pre[i][j+1])/data_pre[i][1]*total);
            }
        }
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
    int max_income=1;
    int max_outcome=1;
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
            qDebug()<<data_pre[i][1]<<"true";
        }

        if(max_income<data_pre[i][0])
        {
            max_income=data_pre[i][0];
        }
        if(max_outcome<data_pre[i][1])
        {
            max_outcome=data_pre[i][1];
        }

    }

    int x=ui->two_widget_first->x();
    int y=ui->two_widget_first->y();
    int height=ui->two_widget_first->height();
    int width=ui->two_widget_first->width();

    if(status)
    {
        QObjectList items=ui->two_widget_first->children();
        int num=items.count();
        for(int i=0;i<num;i++)
        {
            delete items[i];
        }

        items=ui->two_widget_second->children();
        num=items.count();
        for(int i=0;i<num;i++)
        {
            delete items[i];
        }
    }

    int j=1;
    int max=max_outcome;
    if(ui->two_exchange_status->isChecked())
    {
        j=0;
        max=max_income;
    }
    qDebug()<<"max"<<max;

    for(int i=0;i<7;i++)
    {

        QLabel *temp1=new QLabel(ui->two_widget_first);
        QLabel *temp2=new QLabel(ui->two_widget_first);


        temp1->setText(QString::number(data_pre[i][j],10));
        temp1->move(50+60*i,height-80-double(data_pre[i][j])/max*(height-100));
        temp1->setStyleSheet("font: 7pt Castellar;"
                             "color:rgb(105,111,113);");
        temp1->show();

        int month=ui->two_month->currentText().toInt()-6+i;
        if(month<=0)
        {
            month+=12;
        }
        temp2->setText(QString::number(month,10));
        temp2->move(50+60*i,height-55);
        temp2->setStyleSheet("font: 9pt Castellar;"
                             "color:rgb(105,111,113)");
        temp2->show();
    }

    for(int i=0;i<7;i++)
    {
        QLabel *temp3=new QLabel(ui->two_widget_second);
        x=ui->two_widget_second->x();
        y=ui->two_widget_second->y();
        height=ui->two_widget_second->height();

        int month=ui->two_month->currentText().toInt()-6+i;
        if(month<=0)
        {
            month+=12;
        }
        temp3->setText(QString::number(month,10));
        temp3->move(275+60*i,height-80);
        temp3->setStyleSheet("font: 9pt Castellar;"
                             "color:rgb(105,111,113)");
        temp3->show();
    }

    for(int i=1;i<5;i++)
    {
        QLabel *temp=new QLabel(ui->two_widget_second);
        QString content="衣";
        switch(i)
        {
            case 2:
                content="食";
                break;
            case 3:
                content="住";
                break;
            case 4:
                content="其他";
                break;
        }
        temp->setText(content);
        temp->move(15+30,40*i);
        temp->setStyleSheet("font: 25 9pt '微软雅黑 Light' ;"
                            "color:rgb(105,111,113)");
        temp->show();
    }

}

void analyze::on_two_exchange_status_clicked()
{
    if(ui->two_exchange_status->isChecked())
    {
        ui->two_exchange_status->setText("切换支出状态");
    }
    ui->two_icon_exchange->setStyleSheet("background-image: url(:/page/material/支出/收入状态.png);");
    update();

    init_labels(1);
}

void analyze::on_pushButton_4_clicked()
{
    exit(-1);
}
