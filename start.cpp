
#include "ui_start.h"
#include"GAME_define.h"
#include "start.h"
#include<iostream>
using namespace std;


Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    s.setParent(this);
    this->setWindowTitle("拳皇01");
    s.hide();
    this->setFixedSize(WINwidth,WINheight);
    ui->label->setFixedSize(WINwidth,WINheight);
    ui->label->setGeometry(0,0,WINwidth,WINheight);
    ui->push->setGeometry(WINwidth/2-100,WINheight-100,0,0);

    music=new QSoundEffect(this);
    music->setSource(QUrl::fromLocalFile(STARTmus));
    music->setLoopCount(QSoundEffect::Infinite);
    music->setVolume(0.1f);


    m=new QMovie(this);
    m->setScaledSize(QSize(WINwidth,WINheight));
    m->setFileName(START0);
    m->start();
    ui->label->setMovie(m);
    WINtimer.setInterval(10);
    WINtimer.start();
    output();
    connect(&s,&Signin::success,this,[=](){//连接登录成功信号
        p=s.p;//人物信息当前界面
        w.p=p;//复制主界面
        qDebug()<<QString(QString::fromLocal8Bit(w.p.name.c_str()));
        s.close();
        ui->push->setGeometry(WINwidth/2-100,WINheight-100,200,50);//显示按钮
        WINtimer.stop();
    });


}

Start::~Start()
{
    delete ui;
}

void Start::output()
{
    connect(&WINtimer,&QTimer::timeout,this,[=](){
        if(m->currentFrameNumber()+1==m->frameCount())
        {
            m->stop();
             music->play();
            if(m->fileName()==START1)
            {
                m->setFileName(START);
                m->start();//背景地图
                s.show();
            }
            m->setFileName(START1);
            m->start();

        }
    });
}

void Start::on_push_clicked()
{

    this->close();
     w.show();
    music->stop();
}

