#ifndef GAME_COMPUTER_H
#define GAME_COMPUTER_H

#include <QWidget>
#include<QPixmap>
#include<QPaintEvent>
#include<GAME_define.h>
#include<QTimer>
#include<game_base.h>
#include"herores.h"
#include<QSoundEffect>
#include<QPushButton>
#include"game_main.h"
QT_BEGIN_NAMESPACE
namespace Ui { class GAME_computer; }
QT_END_NAMESPACE

class GAME_computer : public GAME_main
{
    Q_OBJECT

public:
    GAME_computer(int lefthero,int rightthero,QWidget *parent =nullptr);
    ~GAME_computer();


    void playgame();//启动游戏
    void Computer(int t);//处理电脑操作
    int Comcontral();//电脑操作返回一个值

    void keyPressEvent(QKeyEvent * ev);//键盘按下事件
    void keyReleaseEvent(QKeyEvent *ev);//键盘松开事件

private:
    Ui::GAME_computer *ui;
};
#endif // GAME_MAIN_H
