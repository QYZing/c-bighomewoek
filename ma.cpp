#include "ma.h"
#include "ui_ma.h"
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QMessageBox>
#include <QPalette>
#define IPserver "101.42.163.22"
ma::ma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ma)
{
    ui->setupUi(this);
    this->setFixedSize(WINwidth,WINheight);
    this->setWindowTitle("拳皇01");
    tcpSocket = new QTcpSocket;
    tcpSocket->connectToHost(IPserver,6666);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connect_success()));

    map.load(MA);
    m=NULL;
    m1=NULL;
    m2=NULL;
    c=NULL;
    c1=NULL;
    c2=NULL;
    k=NULL;
}

ma::~ma()
{
    delete ui;
}

void ma::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,WINwidth,WINheight,map);
}


void ma::on_push_clicked()
{
    int ret;
    std::string msg = ui->message->text().toStdString();
    if(msg=="") goto L1;//空消息跳过发送
     msg='*'+p.name+": "+msg;//消息开头 * 方便辨别
    qDebug()<<QString(QString::fromLocal8Bit(msg.c_str()));
    ret = tcpSocket->write(msg.c_str(),msg.size()+1);
    qDebug("--send:%d--",ret);
    ui->message->setText("");
L1:;
}

void ma::connect_success()
{
    qDebug("success");
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
}
void ma::read_data()
{
    char buf[1024]={};
    tcpSocket->read(buf,sizeof(buf));
    if(buf[0]=='`')
    {

        c2->str=buf;//获取到的动西全放在c2中的str中
        qDebug()<<buf<<" "<<c2->str.c_str()<<"                    这俩个是接受到的";
        emit successip();
        goto L1;
    }
    ui->textEdit->setTextColor(Qt::white);
    ui->textEdit->append(buf);

L1:;

}
void ma::on_pushButton_clicked()//双人对战
{
    ui->pushButton->setEnabled(0);
    QTimer::singleShot(500,this,[=](){
        this->hide();
        c=new Chopeo;
        c->show();
        connect(c,&Chopeo::Close,this,[=](){ //连接选人界面关闭信号
            c->close();
            this->show();
            ui->pushButton->setEnabled(1);
        });

        qDebug()<<"进入界面";
        connect(c,&Chopeo::success,this,[=](){
            qDebug()<<"接受到成功信号";
            m=new GAME_main(c->heroleft,c->heroright);
            m->show();
            connect(m,&GAME_main::Close,this,[=]() {

                qDebug()<<"接受到结束信号";
                k=new KO;
                k->show();
                QTimer::singleShot(3000,this,[=](){
                    m->close();
                    k->close();
                    this->show();
                    if(c!=NULL)
                    {
                        delete c;
                        c=NULL;
                    }
                    if(m!=NULL)
                    {
                        delete m;
                        m=NULL;
                    }
                    if(k!=NULL)
                    {
                        delete k;
                        k=NULL;
                    }

                    ui->pushButton->setEnabled(1);
                });

            });

        });
    });
}


void ma::on_pushButton_2_clicked()//人机
{
     ui->pushButton_2->setEnabled(0);
    QTimer::singleShot(500,this,[=](){
      this->hide();
      c1=new Com_chose;
      c1->show();
      qDebug()<<"进入界面";
      connect(c1,&Com_chose::Close,this,[=](){ //连接选人界面关闭信号
          c1->close();
          this->show();
          ui->pushButton_2->setEnabled(1);

      });
      connect(c1,&Com_chose::success,this,[=](){
          qDebug()<<"接受到成功信号";

      m1=new GAME_computer(c1->heroleft,c1->heroright);
      m1->show();
      connect(m1,&GAME_computer::Close,this,[=]() {
          qDebug()<<"接受到结束信号";
          k=new KO;
          k->show();
          QTimer::singleShot(3000,this,[=](){
              m1->close();
              k->close();
              this->show();
              if(c1!=NULL)
              {
                  delete c1;
                  c1=NULL;
              }
              if(m!=NULL)
              {
                  delete m;
                  m=NULL;
              }
              if(k!=NULL)
              {
                  delete k;
                  k=NULL;
              }
               ui->pushButton_2->setEnabled(1);

          });

      });

   });
    });
}


void ma::on_about_clicked()
{
    QMessageBox::information(this,"关于本软件","拳皇1.0版本\n目前很多地方没有优化，期待下一版本(可能因为作者太懒没有了)\n作者：小团队工作室-（某人，某人，某人)\n以及欢迎来自厦门的(拖拉机上山)提供的素材\n再次铭记几个星期刻苦bug");
}


void ma::on_pushButton_4_clicked()
{
    QMessageBox::information(this,"操作指南","w跳 s下蹲 a左移 d右移 q e基本技能目前没有伤害\nf r z x 技能拥有伤害且释放技能伤害会有变化，右边人物：上下左右 12 基本 3456 技能 ");
}


void ma::on_pushButton_3_clicked()//联机
{
    ui->pushButton_3->setEnabled(0);
    QTimer::singleShot(500,this,[=](){
        this->hide();
        c2=new Udp_chose;
        c2->show();
        qDebug()<<"进入界面";
        connect(c2,&Udp_chose::Close,this,[=](){ //连接选人界面关闭信号
            c2->close();
            if(c2!=NULL) delete c2;
            c2=NULL;
            this->show();
            ui->pushButton_3->setEnabled(1);
        });
        connect(c2,&Udp_chose::success,this,&ma::successIP);

   });
}

void ma::successIP()
{
    qDebug()<<"接受到成功信号";
    tcpSocket->write(c2->str.c_str(),sizeof(c2->str));
    connect(this,&ma::successip,this,[=](){ //寻找到ip
        qDebug()<<"成功接受有到消息这是接收到的字符串";
        int n1=c2->str[1]-'0'; //1号位置存n
        int le=-1,ri=-1;

        if(n1==1)
        {
            le=c2->hernum;
            ri=c2->str[2]-'0';//2号存英雄编号
        }
        else
        {
            ri=c2->hernum;
            le=c2->str[2]-'0';
        }
        qDebug()<<le<<"这是英雄编号";
        char po[1024]={0};
        for(int i=3;i<c2->str.size();i++)
        {
            po[i-3]=c2->str[i];//获取对方地址
        }
        qDebug()<<"***************************************************"<<c2->str.c_str();
        c2->close();
        m2=new Udp_game(n1,le,ri,QString(po));
        m2->show();

        connect(m2,&Udp_game::Close,this,[=]() {
            qDebug()<<"接受到结束信号";
            k=new KO;
            k->show();
            QTimer::singleShot(3000,this,[=](){
                m2->close();
                k->close();
                this->show();
                if(c2!=NULL)
                {
                    delete c2;
                    c2=NULL;
                }
                if(m2!=NULL)
                {
                    delete m2;
                    m2=NULL;
                }
                if(k!=NULL)
                {
                    delete k;
                    k=NULL;
                }

                ui->pushButton_3->setEnabled(1);

            });
        });
    });
}
