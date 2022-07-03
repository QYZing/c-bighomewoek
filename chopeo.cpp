#include "chopeo.h"
#include "ui_chopeo.h"
#include<QPainter>
#include"GAME_define.h"
Chopeo::Chopeo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chopeo)
{
    ui->setupUi(this);
    this->setWindowTitle("拳皇01");
    map.load(":/res/xuanren.png");
    map2.load(":/res/vs.png");
    map2=map2.scaled(ui->label->width(),ui->label->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(map2);
    heroleft=-1;
    heroright=-1;
    timer.setInterval(1);
    hro();
  //  update();


}

Chopeo::~Chopeo()
{
    delete ui;
}
void Chopeo::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,WINwidth,WINheight,map);
    qDebug()<<"选人开始";

}

void Chopeo::hro()
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


void Chopeo::on_A1_clicked()
{
       heroleft=0;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Chopeo::on_A2_clicked()
{
       heroleft=1;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Chopeo::on_A3_clicked()
{
       heroleft=2;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Chopeo::on_A4_clicked()
{
       heroleft=3;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Chopeo::on_A5_clicked()
{
    heroleft=4;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Chopeo::on_B1_clicked()
{
     heroright=0;
    ui->B1->setEnabled(0);
    ui->B2->setEnabled(0);
    ui->B3->setEnabled(0);
    ui->B4->setEnabled(0);
    ui->B5->setEnabled(0);
}


void Chopeo::on_B2_clicked()
{
     heroright=1;
    ui->B1->setEnabled(0);
    ui->B2->setEnabled(0);
    ui->B3->setEnabled(0);
    ui->B4->setEnabled(0);
    ui->B5->setEnabled(0);
}


void Chopeo::on_B3_clicked()
{
     heroright=2;
    ui->B1->setEnabled(0);
    ui->B2->setEnabled(0);
    ui->B3->setEnabled(0);
    ui->B4->setEnabled(0);
    ui->B5->setEnabled(0);
}


void Chopeo::on_B4_clicked()
{
     heroright=3;
    ui->B1->setEnabled(0);
    ui->B2->setEnabled(0);
    ui->B3->setEnabled(0);
    ui->B4->setEnabled(0);
    ui->B5->setEnabled(0);
}


void Chopeo::on_B5_clicked()
{
    heroright=4;
    ui->B1->setEnabled(0);
    ui->B2->setEnabled(0);
    ui->B3->setEnabled(0);
    ui->B4->setEnabled(0);
    ui->B5->setEnabled(0);

}


void Chopeo::on_pushButton_clicked()
{
    emit  this->Close();
}

