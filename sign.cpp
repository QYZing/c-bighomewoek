#include "sign.h"
#include "ui_sign.h"
#include"GAME_define.h"
#include<QMessageBox>
#include<QPainter>
sign::sign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sign)
{
    ui->setupUi(this);
    this->setWindowTitle("拳皇01");
    map.load(":/res/zh.png");

}

sign::~sign()
{
    delete ui;
}
void sign::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,WINwidth,WINheight,map);
}

void sign::on_push_clicked()
{
    string a=ui->id->text().toStdString();
    string b=ui->pin->text().toStdString();
    string c=ui->name->text().toStdString();
    if(!a.size()||!b.size()||!c.size())
    {
        QMessageBox::information(this,"提示","账号密码昵称不能为空");
        goto L1;
    }
    for(int i=0;i<a.size();i++)
    {
        if(a[i]<'0'||a[i]>'9')
        {
            QMessageBox::information(this,"提示","账号只能是数字");
            goto L1;
        }
    }
    p.ID=a;
    p.pin=b;
    p.name=c;
    emit zhuce();
L1:;
}

