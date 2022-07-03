#include "ko.h"
#include "ui_ko.h"
#include<GAME_define.h>
#include<QPainter>
KO::KO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KO)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog );
    setWindowModality(Qt::WindowModal);
    this->setWindowTitle("拳皇01");
    this->setFixedSize(WINwidth/2,WINheight/2);

    music=new QSoundEffect(this);
    music->setSource(QUrl::fromLocalFile(KOSound));
    music->setLoopCount(QSoundEffect::Infinite);
    music->setVolume(0.1f);
    music->play();
    music->setLoopCount(1);

    map.load(KOmap);
    map=map.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->grabKeyboard();
}
void KO::paintEvent(QPaintEvent *)//画图
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),map);
}
KO::~KO()
{
    delete ui;
}



