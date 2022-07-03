#include "signin.h"
#include "ui_signin.h"
#include<QMessageBox>
#define IPserver "101.42.163.22"
//"192.168.0.103"

#include<QDebug>
Signin::Signin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);
//    s.setParent(this);
//    s.hide();
    setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog );
    setWindowModality(Qt::WindowModal);
    tcpSocket = new QTcpSocket;
    tcpSocket->connectToHost(IPserver,6666);//绑定ip和端口
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connect_success()));
    connect(&s,&sign::zhuce,this,[=](){
        p=s.p;//把基本信息拷贝过来
        s.close();//关闭界面
        this->show();
        string t="/";//下划线用来注册
        t=t+p.ID+'%'+p.pin+'$'+p.name;   //分割符号;
        tcpSocket->write(t.c_str(),sizeof(t));       //
    });
}

Signin::~Signin()
{
    delete ui;
}

void Signin::on_sign_clicked()
{
   // this->hide();
    s.show();
}

void Signin::connect_success()
{
    qDebug()<<"success";
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
}

void Signin::read_data()
{
    char buf[1024]={};//接受消息
    buf[0]='?';
    tcpSocket->read( buf,sizeof(buf));
    qDebug()<<buf[0];
    if(buf[0]=='?')
    {
        QMessageBox::information(this,"提示","账号或密码错误");
        goto L1;
    }
    else if(buf[0]=='/')//注册成功
    {
        QMessageBox::information(this,"提示","注册成功请登录");
        goto L1;
    }
    else if(buf[0]=='&')
    {
         QMessageBox::information(this,"提示","账号重复请重新注册");
         goto L1;
    }
    else if(buf[0]=='%')
    {
        char *f=buf+1;
        string buf1=f;
       p.name=buf1;//接受昵称
          qDebug()<<QString(QString::fromLocal8Bit(buf1.c_str()));
       emit success();//发送登录成共信号
    }
    L1:;
}

void Signin::on_push_clicked()
{

    qDebug()<<"emmmmm";
    std::string id=ui->ID->text().toStdString();
    std::string pin=ui->PIN->text().toStdString();
    if(!id.size()||!pin.size())
    {
        QMessageBox::information(this,"提示","账号或密码不能为空");
        goto L1;
    }

    for(int i=0;i<id.size();i++)
    {
        if(id[i]<'0'||id[i]>'9')
        {
            QMessageBox::information(this,"提示","账号只能是数字");
            goto L1;
        }
    }

    id='?'+id+"%"+pin;//账号密码用%隔开；
    //?用来登录
    // / 注册
    p.ID=id;
    p.pin=pin;
    tcpSocket->write(id.c_str(),id.size()+1);


L1:;
}

