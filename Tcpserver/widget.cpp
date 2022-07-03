//widget.cpp
#include "widget.h"
#include "ui_widget.h"
#define IPserver "101.42.163.22"
#include"people.h"
#include<string>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ipa1=-1;
    ipb1=-1;
    file.open("peo.txt",ios::in);
    string a,b,c;
    while(file>>a>>b>>c)
    {
        people pe;
        pe.ID=a;
        pe.pin=b;
        pe.name=c;
        p.push_back(pe);

    }
    file.close();

    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,6666);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(new_connect()));
}

Widget::~Widget()
{
    file.open("peo.txt",ios::out);
    for(int i=0;i<p.size();i++)
    {
        file<<p[i].ID<<" "<<p[i].pin<<" "<<p[i].name<<endl;
    }
    file.close();
    delete ui;
}

void Widget::new_connect()
{
    qDebug("--new connect--");
    QTcpSocket* tcpSocket = tcpServer->nextPendingConnection();

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
    socketArr.push_back(tcpSocket);
    qDebug()<<tcpSocket->peerAddress();
    qDebug()<<tcpSocket->peerPort();


}

void Widget::read_data()
{
    for(long long  i=0; i<socketArr.size(); i++)
    {
        if(socketArr[i]->bytesAvailable())
        {
            char buf[1024] = {};
            socketArr[i]->read(buf,sizeof(buf));

            char buf2[1024] = {};
            sprintf(buf2,"%d:%s",i,buf);
            ui->textEdit->append(buf2);//读取到屏幕上

            if(buf[0]=='?')//登录信号
            {
                //发送信号找文件判断
              char *c=buf;
              string a="";//账号
              while(*++c!='%')
              {
                  a+=*c;
              }
              string b="";//密码
              while(*++c!='\0')
              {
                    b+=*c;
              }
              string te="?";
              for(int o=0;o<p.size();o++)
              {
                  if(p[o].ID==a)
                    if(p[o].pin==b) {
                        te='%'+p[o].name;
                          qDebug()<<QString(QString::fromLocal8Bit(te.c_str()));
                        break;
                    }
              }
                socketArr[i]->write(te.c_str(),sizeof te);
            }
            else if(buf[0]=='/') //注册信号
            {
                  people pe;
                char *c=buf;
                string a="";//账号
                while(*++c!='%')
                {
                    a+=*c;
                }
                string b="";//密码
                while(*++c!='$')
                {
                      b+=*c;
                }
                string c1="";//昵称
//                while(*++c!='\0')
//                {
//                    c1+=*c;
//                }
                c=c+1;
                c1+=c;
                char te;
                for(int o=0;o<p.size();o++)
                {
                    if(p[o].ID==a)
                    {

                         te='&';
                      //  socketArr[i]->write(&te,sizeof(te));//&代表重复
                        goto L1;
                    }
                }

                pe.ID=a;pe.pin=b;pe.name=c;
                p.push_back(pe);
                te='/';//发送成功注册信号
                 L1:; socketArr[i]->write(&te,sizeof(te));

            }
            else if(buf[0]=='`')
            {qDebug()<<"处理联机信息";
                if(ipa1==-1&&ipb1==-1)
                {
                     ipa1=i;
              //       ipb="`2";//人物编号
               //      ipb=ipb+buf[1];//再加上英雄编号

             //        ipb+=(buf+1);
                     ipb="`2";
                     ipb+=(buf+1);

                     qDebug()<<QString(QString::fromLocal8Bit(ipb.c_str()));
                }
                else if(ipb1==-1&&ipa1!=-1)
                {
                    ipb1=i;

                    ipa="`1";
                    ipa+=(buf+1);
                    socketArr[ipa1]->write(ipa.c_str(),sizeof(ipa)+1);
                    socketArr[ipb1]->write(ipb.c_str(),sizeof(ipb)+1);
                   qDebug()<<QString(QString::fromLocal8Bit(ipa.c_str()));
                   ipa="";
                   ipb="";

                    ipa1=-1;
                    ipb1=-1;
                }
            }
            else if(buf[0]=='*')
            for(int j=0; j<socketArr.size(); j++)//分发消息给每个人
            {
                char buf1[1024] = {};
                sprintf(buf1,"%s",buf+1);
                socketArr[j]->write(buf1,sizeof(buf1));
            }
        }
    }
}
