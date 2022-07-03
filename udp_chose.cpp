#include "udp_chose.h"
#include "ui_udp_chose.h"
#include<GAME_define.h>
#include<QPainter>
#include<QMessageBox>
#include<QHostAddress>
#include<QNetworkInterface>
Udp_chose::Udp_chose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Udp_chose)
{
    ui->setupUi(this);

    this->setFixedSize(WINwidth,WINheight);
    this->setWindowTitle("拳皇01");
    map.load(":/res/Com_01.png");
    timer.setInterval(20);
    ui->label->hide();
    hernum=-1;
    N=-1;


}

Udp_chose::~Udp_chose()
{
    delete ui;
}


void Udp_chose::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,WINwidth,WINheight,map);

}
void Udp_chose::on_pushButton_clicked()
{
    string  t;
    if(hernum==-1)
    {
        QMessageBox::information(this,"提示","请选择人物");
         goto L1;
    }

    t=(hernum+'0');
    str='`'+t+read_ip_address().toStdString();
    emit success();
    ui->pushButton->setEnabled(0);
    ui->label->show();
    L1:;
}

QString Udp_chose::read_ip_address()
{
    QString ip_address;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
       if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  ipAddressesList.at(i).toIPv4Address())
       {
          ip_address = ipAddressesList.at(i).toString();
          qDebug()<<ip_address;  //debug
          //break;
        }
      }
       if (ip_address.isEmpty())
          ip_address = QHostAddress(QHostAddress::LocalHost).toString();
       return ip_address;
}
void Udp_chose::on_A1_clicked()
{
    hernum=0;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Udp_chose::on_A2_clicked()
{
    hernum=1;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Udp_chose::on_A3_clicked()
{
    hernum=2;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Udp_chose::on_A4_clicked()
{
    hernum=3;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}


void Udp_chose::on_A5_clicked()
{
    hernum=4;
    ui->A1->setEnabled(0);
    ui->A2->setEnabled(0);
    ui->A3->setEnabled(0);
    ui->A4->setEnabled(0);
    ui->A5->setEnabled(0);
}



void Udp_chose::on_pushButton_2_clicked()
{
    emit Close();
}

