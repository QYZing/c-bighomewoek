#include "com_chose.h"
#include "ui_com_chose.h"
#include<QPainter>
#include"GAME_define.h"
Com_chose::Com_chose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Com_chose)
{
    ui->setupUi(this);
    this->setFixedSize(WINwidth,WINheight);
    this->setWindowTitle("拳皇01");
    map.load(":/res/Com_01.png");
    timer.setInterval(20);
    heroleft=-1;
    heroright=-1;
    hro();
}

Com_chose::~Com_chose()
{
    delete ui;
}
void Com_chose::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,WINwidth,WINheight,map);
    qDebug()<<"选人开始";

}
void Com_chose::hro()
{
    timer.start();
    connect(&timer,&QTimer::timeout,this,[=](){
        if(heroleft!=-1&&heroright!=-1)//防止多次创造
        {
            qDebug()<<"发送选人成功信号";
            emit success();
            this->close();
            heroleft=-1;
            heroright=-1;
        }
    });
}


void Com_chose::on_A1_clicked()
{
    heroleft=0;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Com_chose::on_A2_clicked()
{
    heroleft=1;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Com_chose::on_A3_clicked()
{
    heroleft=2;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Com_chose::on_A4_clicked()
{
    heroleft=3;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Com_chose::on_A5_clicked()
{
    heroleft=4;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Com_chose::on_pushButton_clicked()
{
    heroright=0;
    ui->pushButton->setEnabled(0);
}


void Com_chose::on_pushButton_2_clicked()
{
    emit Close();
}




