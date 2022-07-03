#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <QWidget>
#include<QPixmap>
#include<QPaintEvent>
#include<GAME_define.h>
#include<QTimer>
#include<game_base.h>
#include"herores.h"
#include<QSoundEffect>
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class GAME_main; }
QT_END_NAMESPACE

class GAME_main : public QWidget
{
    Q_OBJECT

public:
    GAME_main(int lefthero,int rightthero,QWidget *parent =nullptr);
    ~GAME_main();

    HERORES hres[HERONUMBER*4];//全英雄技能绑定 *4 每个有4个技能
    QPixmap map;//背景地图
    QSoundEffect *music;//背景音乐

    int heroleft;
    int heroright;
    GAME_base hero;//人物基类
    GAME_base hero2;//人物基类
    bool  ONCE;

    void initScence();//初始化 左边人物
    void initScence2();//右边人物
    void playgame();//启动游戏
    void updateinput(GAME_base &hero,GAME_base &hero2);//根据用户输入的数据有关更新

    void paintEvent(QPaintEvent *);//绘制初始图像
    void updateagain();//绘制后面图象

    void keyPressEvent(QKeyEvent * ev);//键盘按下事件
    void keyReleaseEvent(QKeyEvent *ev);//键盘松开事件

    QTimer WINtimer;//游戏帧数

    //QPushButton *push;
signals:
    void Close();

private:
    Ui::GAME_main *ui;

};
#endif // GAME_MAIN_H
