#ifndef UDP_GAME_H
#define UDP_GAME_H

#include <QWidget>
#include"game_computer.h"
#include<QUdpSocket>
#include<QString>
#include<QTimer>
namespace Ui {
class Udp_game;
}
struct KEY
{
    QString a;
    int key()
    {
        QString b=a.mid(2);
        qDebug()<<"转换完成的字符是"<<b;
        return b.toInt();
    }
    QString type()
    {
        return a[0];
    }
   bool isAutoRepeat()
   {
       if(a[1]=='1') return 1;
       else return 0;
   }
};

class Udp_game : public GAME_main
{
    Q_OBJECT

public:
    explicit Udp_game(int n,int lefthero,int rightthero,QString ip,QWidget *parent =nullptr);
    ~Udp_game();
    QUdpSocket *socket;
    QString IP;//对手ip
    int port;


    int N;//自己是一号人物还是二号人物
    bool Ns;
    void playgame();//启动游戏

   // long int e;//收对方的值
    KEY ek;
    //QKeyEvent *e;
    void He(KEY ev);
    void He1(KEY ev);


    void keyPressEvent(QKeyEvent * ev);//键盘按下事件 //处理网上对方传递的值进行本地操作
    void keyReleaseEvent(QKeyEvent *ev);//键盘松开事件

private:
    Ui::Udp_game *ui;
};

#endif // UDP_GAME_H
