#include "wish_bottle.h"
#include "ui_wish_bottle.h"

wish_bottle::wish_bottle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wish_bottle)
{
    ui->setupUi(this);
    QIntValidator *validator_for_showmoney=new QIntValidator(0,1000000,this);
    ui->w3_lineEdit->setValidator(validator_for_showmoney);

    set_info();
    update();

}

void wish_bottle::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QSqlQuery query;
    QWidget::paintEvent(event);

    query.exec("select * from analyze");

    int surplus=0;
    while(query.next())
    {
        int outcome=-query.record().value("outcome").toInt();
        int budget=query.record().value("budget").toInt();
        if(outcome<budget)
        {
            surplus+=budget-outcome;
        }
    }
    qDebug()<<"surplus1"<<surplus;
    query.exec("select * from wish");
    int count=0;
    while(query.next())
    {
        count++;
    }
    qDebug()<<"count"<<count;
    query.exec("select * from wish");
    for(int i=1;i<=count-3;i++)
    {
        query.next();
        surplus-=query.record().value("money").toInt();
        qDebug()<<"surplus2"<<surplus;
    }

    QColor color[2];
    color[0]=QColor(65,193,235);
    //color[0]=QColor(0,0,0);

    color[1]=QColor(249,250,252);

    for(int i=1;i<=3;i++)
    {
        int x=0;
        int y=0;
        switch(i)
        {
            case 1:
                x=ui->wish_1->x();
                y=ui->wish_1->y();
                break;
            case 2:
                x=ui->wish_2->x();
                y=ui->wish_2->y();
                break;
            case 3:
                x=ui->wish_3->x();
                y=ui->wish_3->y();
                break;
        }
        //painter1(ui->wish_1);
        if(query.next())
        {
            int money=query.record().value("money").toInt();
            qDebug()<<"money"<<money;
            if(money>surplus)
            {
                painter.setPen(color[0]);
                painter.setBrush(color[0]);
                painter.setRenderHint(QPainter::Antialiasing,true);
                painter.drawPie(x+60,y+270,90,90,0,360*16*double(surplus)/money);
                qDebug()<<"drawpie successfully";
                painter.setPen(color[1]);
                painter.setBrush(color[1]);
                painter.drawPie(x+70,y+280,70,70,0,360*16*double(surplus)/money);
                surplus=0;
            }
            else
            {
                painter.setPen(color[0]);
                painter.setBrush(color[0]);
                painter.setRenderHint(QPainter::Antialiasing,true);
                painter.drawPie(x+60,y+270,90,90,0,360*16*double(surplus)/money);

                painter.setPen(color[1]);
                painter.setBrush(color[1]);
                painter.drawPie(x+70,y+280,70,70,0,360*16*double(surplus)/money);
                surplus-=money;
            }

        }
        else
        {

        }
    }
}

void wish_bottle::set_info()
{
    QSqlQuery query;
    query.exec("select * from analyze");

    int surplus=0;
    while(query.next())
    {
        int outcome=-query.record().value("outcome").toInt();
        int budget=query.record().value("budget").toInt();
        if(outcome<budget)
        {
            surplus+=budget-outcome;
        }
    }

    query.exec("select * from wish");
    int count=0;
    while(query.next())
    {
        count++;
    }

    query.exec("select * from wish");
    for(int i=1;i<=count-3;i++)
    {
        query.next();
        surplus-=query.record().value("money").toInt();
        qDebug()<<"surplus2"<<surplus;
    }

    for(int i=1;i<=3;i++)
    {
        QLabel *label;
        QTextBrowser *browser;
        QWidget *label_back;
        QLabel *label_in;

        switch(i)
        {
            case 1:
                label=ui->wish_1_percent;
                browser=ui->textBrowser;
                label_back=ui->widget_1;
                label_in=ui->label_2;
                //line=ui->w1_lineEdit;
                //label_money=ui->w1_label_money;
                break;
            case 2:
            label=ui->wish_2_percent;
            browser=ui->textBrowser_2;
            label_back=ui->widget_2;
            label_in=ui->label_6;
            //line=ui->w2_lineEdit;
            //label_money=ui->w2_label_money;
            break;
            case 3:
            label=ui->wish_3_percent;
            browser=ui->textBrowser_3;
            label_back=ui->widget_3;
            label_in=ui->label_7;
            break;
        }
        //painter1(ui->wish_1);
        if(query.next())
        {
            int money=query.record().value("money").toInt();
            qDebug()<<"money123"<<money;
            if(money>surplus)
            {
                int percent=int(double(surplus)/money*100);
                label->setText(QString::number(percent,10)+"%");
                label->raise();
                browser->setPlainText(query.record().value("wish").toString());

                label_back->setStyleSheet("QWidget{background-image: url(:/WishBottle/material/wish_bottle/瓶子.png);}");

                int x=label_in->x();
                int y=label_in->y();
                int width=label_in->width();
                int height=label_in->height();
                y+=(1-double(surplus)/money)*height;
                qDebug()<<"y"<<y;
                height=double(double(surplus)/money)*double(height);
                qDebug()<<"height"<<height;
                label_in->setGeometry(x,y,width,height);
                //label_in->resize(height,width);
                //label
                label_in->show();
                //label_in->setText("here");
                if(!label_in->isVisible())
                {
                    label_in->show();
                }
                label_in->setStyleSheet("background-image: url(:/WishBottle/material/wish_bottle/stars.png);"
                                        "background-color: rgba(255, 255, 255, 0);");
                //ui->frame->setAutoFillBackground(true);
                //QPalette palette = ui->frame->palette();
                /*palette.setBrush(QPalette::Window,
                    QBrush(QPixmap(":/WishBottle/material/wish_bottle/待存储.png").scaled( // 缩放背景图.
                                                size(),
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation))); // 使用平滑的缩放方式
                //setPalette(palette);
*/

                ui->wish_1_fill->setStyleSheet("border-image: url(:/wish_bottle/material/心愿/进度2.png);"
                                               "background-color: rgba(255, 255, 255, 0);");
                if(i==3)
                {
                    ui->w3_label_money->hide();
                    ui->w3_lineEdit->hide();
                    ui->textBrowser_3->show();
                }

                surplus=0;

            }
            else
            {
                int percent=int(double(surplus)/money*100);
                label->setText(QString::number(percent,10)+"%");
                label->raise();
                browser->setPlainText(query.record().value("wish").toString());
                label_back->setStyleSheet("background-image: url(:/WishBottle/material/wish_bottle/瓶子.png);");
                label_in->setStyleSheet("background-image: url(:/WishBottle/material/wish_bottle/stars.png);"
                                        "background-color: rgba(255, 255, 255, 0);");
                if(label_in->isHidden())
                {
                    label_in->show();
                    label_in->raise();
                }

                surplus-=money;

                if(i==3)
                {
                    ui->w3_label_money->hide();
                    ui->w3_lineEdit->hide();

                    ui->textBrowser_3->show();
                }


            }

        }
        else
        {
            label->setText(" ");

            label_back->setStyleSheet("QWidget{background-image: url(:/WishBottle/material/wish_bottle/待存储.png);}");
            label_in->hide();
            if(i==3)
            {
                ui->w3_label_money->show();
                ui->w3_lineEdit->show();
                ui->textBrowser_3->hide();

                text=new QTextEdit(ui->wish_3_content);
                text->setGeometry(20,50,170,181);
                text->setStyleSheet("border-image: null;"
                                    "background-color: rgba("
                                    "240,241,242,0);");
                text->show();
            }
        }
    }
}

wish_bottle::~wish_bottle()
{
    delete ui;
}

void wish_bottle::on_pushButton_4_clicked()
{
    exit(-1);
}

void wish_bottle::on_add_wish_clicked()
{
    if(ui->w3_lineEdit->text().isEmpty()||text->toPlainText().isEmpty())
    {
        QMessageBox::critical(0,"Cannot submit!",
                              "please complish!",QMessageBox::Cancel);
    }
    else
    {
        QSqlQuery query;
        query.prepare("insert into wish (money,wish,status,surplus)values(:money,:wish,0,0)");
        query.bindValue(":money",ui->w3_lineEdit->text().toInt());
        query.bindValue(":wish",text->toPlainText());
        query.exec();
        QMessageBox::information(NULL,"Information","Submit successfully");
        ui->w3_lineEdit->clear();
        text->clear();
    }
    set_info();
    update();
}
