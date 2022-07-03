#ifndef MA_H
#define MA_H

#include <QWidget>
#include"GAME_define.h"
#include<QPixmap>
#include"chopeo.h"
#include"ko.h"
#include"com_chose.h"
#include"people.h"
#include<QTcpSocket>
#include"game_computer.h"
#include"udp_chose.h"
#include"udp_game.h"
namespace Ui {
class ma;
}

class ma : public QWidget
{
    Q_OBJECT

public:
    explicit ma(QWidget *parent = nullptr);
    ~ma();
    QPixmap map;
    void paintEvent(QPaintEvent *);//绘制初始图像
    Chopeo *c;//双人选人界面
    Com_chose *c1;//人机选人界面
    Udp_chose *c2;//联机选人界面

    GAME_main *m;//人人
    GAME_computer *m1;//人机
    Udp_game *m2;//联机

    KO *k;//ko界面
    people p;//人物信息
   QTcpSocket* tcpSocket;//与服务器绑定的套接字，用语发送信息
    void successIP();//网络游戏界面的槽函数



signals:
   void successip();//联机成功获取ip
private slots:
    void on_pushButton_clicked();

    void connect_success();
    void read_data();
    void on_push_clicked();

    void on_pushButton_2_clicked();

    void on_about_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ma *ui;
};

#endif // MA_H
