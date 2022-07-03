#include "udp_game.h"
#include "ui_udp_game.h"
Udp_game::Udp_game(int n, int lefthero, int rightthero,QString ip, QWidget *parent ) :
    GAME_main( lefthero, rightthero, parent ),IP(ip),
    N(n),ui(new Ui::Udp_game)
{
    ui->setupUi(this);
    socket=new QUdpSocket(this);
  //  e=0;
    port=9999;
    socket->bind(port);//绑定端口
    Ns=0;
    connect(socket,&QUdpSocket::readyRead,this,[=](){

        char Str[1024]={0};
        qDebug()<<"启用接受信号";

        socket->readDatagram(Str,sizeof(Str));
        ek.a=QString(Str);
        qDebug()<<ek.a;
        qDebug()<<"可以收取对方消息";
        qDebug()<<ek.type();//<<" "<<ek.key();
        if(ek.type()=="p")
        {
          //  Ns=1;
            He(ek);//键盘按下事件 //处理网上对方传递的值进行本地操作
          qDebug()<<"键盘案件有效"<<ek.key();
           // Ns=0;
        }
        else if(ek.type()=="R")
        {
          //  Ns=1;
              He1(ek);
          //  Ns=0;
        }
    });
    playgame();

}

Udp_game::~Udp_game()
{
    delete ui;
}

void Udp_game::playgame()
{
    // qDebug()<<1;
    WINtimer.start();//相当于循环
    connect(&WINtimer,&QTimer::timeout,this,[=](){//接受定时器发送信号

        /*********************和用户有关的变量更新************************/
        //按键自动调用
        /**********************************************************************/

        /******************生命值,位置的更新*************************/
      //  He(e);//处理对方发送信息
     //   qDebug()<<"---------------------------------"<<e;
      //  e=0;
        updateinput(hero,hero2);//用户交互
        updateinput(hero2,hero);//用户交互
        updateagain();  //显示人物画面

        if(hero.Life<=0||hero2.Life<=0)
        {
            music->stop();
            hero.Movie.stop();
            hero2.Movie.stop();
            emit this->Close();
            qDebug()<<"发送结束信号";
            WINtimer.stop();
            hero.Life=1;
            hero2.Life=1;
        }/*/////////////////////////////////////////----------------------------------/////////结束*/

    });

}

void Udp_game::He(KEY ev)
{
    if(ev.key()==Qt::Key_D)
    {
        qDebug()<<"d";
        hero.Movexy=MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero.Freeskill) //播放技能时候不播放动作
            if(hero.Movie.fileName()!=hero.Herogiffile[Righ]||!ev.isAutoRepeat())//不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {

                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Righ]);//gif存到movie 里

            }

    }
    else if(ev.key()==Qt::Key_A)
    {
        qDebug()<<"A";
        hero.Movexy=-MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Lef]||!ev.isAutoRepeat()) //不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Lef]);  //gif存到movie 里
                // hero.Movie.start();

            }
    }
    else if(ev.key()==Qt::Key_W&&hero.Xy.y==HEROlefty)//跳跃，只能一段跳
    {
        qDebug()<<"W";
        hero.Jump=JUMPstrart;

        hero.Movie.stop();
        hero.Movie.setFileName(hero.Herogiffile[To]);  //gif存到movie 里
            //  qDebug()<<hero.Herogiffile[Top];

    }
    else if(ev.key()==Qt::Key_S&&hero.Xy.y==HEROlefty)//蹲下
    {
        qDebug()<<"S";
            //if(hero.Movie.currentFrameNumber()==1) hero.Movie.stop();
        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Dow]||!ev.isAutoRepeat())
            {

                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Dow]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }

    else if(ev.key()==Qt::Key_Q)//1
    {
        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Qq]||!ev.isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Qq]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_E)//2
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Ee]||!ev.isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Ee]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_F)//3
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Ff]||!ev.isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Ff]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_R)//4
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Rr]||!ev.isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Rr]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_Z)//5
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Zz]||!ev.isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Zz]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_X)//6
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Xx]||!ev.isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Xx]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_Right)
    {
        qDebug()<<"d";
        hero2.Movexy=MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero2.Freeskill) //播放技能时候不播放动作
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Righ]||!ev.isAutoRepeat())//不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {

                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Righ]);//gif存到movie 里

            }

    }
    else if(ev.key()==Qt::Key_Left)
    {
        qDebug()<<"A";
        hero2.Movexy=-MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Lef]||!ev.isAutoRepeat()) //不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Lef]);  //gif存到movie 里
                // hero.Movie.start();

            }
    }
    else if(ev.key()==Qt::Key_Up&&hero2.Xy.y==HEROlefty)//跳跃，只能一段跳
    {
        qDebug()<<"W";
        hero2.Jump=JUMPstrart;

        hero2.Movie.stop();
        hero2.Movie.setFileName(hero2.Herogiffile[To]);  //gif存到movie 里
            //  qDebug()<<hero.Herogiffile[Top];

    }
    else if(ev.key()==Qt::Key_Down&&hero2.Xy.y==HEROlefty)//蹲下
    {
        qDebug()<<"S";
            //if(hero.Movie.currentFrameNumber()==1) hero.Movie.stop();
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Dow]||!ev.isAutoRepeat())
            {

                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Dow]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }

    else if(ev.key()==Qt::Key_1)
    {
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Qq]||!ev.isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Qq]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_2)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Ee]||!ev.isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Ee]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_3)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Ff]||!ev.isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Ff]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_4)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Rr]||!ev.isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Rr]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_5)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Zz]||!ev.isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Zz]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev.key()==Qt::Key_6)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Xx]||!ev.isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Xx]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }


}
void Udp_game::He1(KEY ev)
{
    if(ev.key()==Qt::Key_D)
    {

        if(!ev.isAutoRepeat())//按下起来
        {
            hero.Movexy=0;
            initScence();

        }

    }
    else if(ev.key()==Qt::Key_A)
    {
        if(!ev.isAutoRepeat())//按下起来
        {
            hero.Movexy=0;
            initScence();
        }

    }
    else if(ev.key()==Qt::Key_S)
    {
        if(!ev.isAutoRepeat())//按下起来
        {
            initScence();
        }

    }
    else if(ev.key()==Qt::Key_W)
    {

        if(!ev.isAutoRepeat())//按下起来
        {
            initScence();
        }

    }
    else if(ev.key()==Qt::Key_Q)
    {
        if(!ev.isAutoRepeat()&&(!hero.Freeskill) )//按下起来
        {
            initScence();
        }
    }
    else if(ev.key()==Qt::Key_E)
    {
        if(!ev.isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev.key()==Qt::Key_F)
    {
        if(!ev.isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev.key()==Qt::Key_R)
    {
        if(!ev.isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev.key()==Qt::Key_Z)
    {
        if(!ev.isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev.key()==Qt::Key_X)
    {
        if(!ev.isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev.key()==Qt::Key_Right)
    {

        if(!ev.isAutoRepeat())//按下起来
        {
            hero2.Movexy=0;
            initScence2();

        }

    }
    else if(ev.key()==Qt::Key_Left)
    {
        if(!ev.isAutoRepeat())//按下起来
        {
            hero2.Movexy=0;
            initScence2();
        }

    }
    else if(ev.key()==Qt::Key_Down)
    {
        if(!ev.isAutoRepeat())//按下起来
        {
            initScence2();
        }

    }
    else if(ev.key()==Qt::Key_Up)
    {

        if(!ev.isAutoRepeat())//按下起来
        {
            initScence2();
        }

    }
    else if(ev.key()==Qt::Key_1)
    {
        if(!ev.isAutoRepeat()&&(!hero2.Freeskill) )
        {
            initScence2();
        }
    }
    else if(ev.key()==Qt::Key_2)
    {
        if(!ev.isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }
    else if(ev.key()==Qt::Key_3)
    {
        if(!ev.isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }
    else if(ev.key()==Qt::Key_4)
    {
        if(!ev.isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }
    else if(ev.key()==Qt::Key_5)
    {
        if(!ev.isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }
    else if(ev.key()==Qt::Key_6)
    {
        if(!ev.isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }

}
void Udp_game::keyPressEvent(QKeyEvent *ev)
{
    if(N==1&&(ev->key()==Qt::Key_D||ev->key()==Qt::Key_A||ev->key()==Qt::Key_W||ev->key()==Qt::Key_S||ev->key()==Qt::Key_F
                   ||ev->key()==Qt::Key_R||ev->key()==Qt::Key_Z||ev->key()==Qt::Key_X||ev->key()==Qt::Key_Q||ev->key()==Qt::Key_E
                   ))
    {


        QString p1;
        if(ev->isAutoRepeat()) p1="p1";
        else p1="p0";
        p1=p1+QString::number(ev->key());
        socket->writeDatagram(p1.toUtf8(),sizeof(p1),QHostAddress(IP),port);

        qDebug()<<"发送自身信息到对方"<<p1;
    }
    else if(N==2&&(ev->key()==Qt::Key_Left||ev->key()==Qt::Key_Right||ev->key()==Qt::Key_1||ev->key()==Qt::Key_2||ev->key()==Qt::Key_3
                        ||ev->key()==Qt::Key_4||ev->key()==Qt::Key_5||ev->key()==Qt::Key_6||ev->key()==Qt::Key_Down||ev->key()==Qt::Key_Up
                 ))
    {

       QString p1;
       if(ev->isAutoRepeat()) p1="p1";
       else p1="p0";
       p1=p1+QString::number(ev->key());
       socket->writeDatagram(p1.toUtf8(),sizeof(p1),QHostAddress(IP),port);

    }
    else if((N==1)&&(ev->key()==Qt::Key_Left||ev->key()==Qt::Key_Right||ev->key()==Qt::Key_1||ev->key()==Qt::Key_2||ev->key()==Qt::Key_3
                        ||ev->key()==Qt::Key_4||ev->key()==Qt::Key_5||ev->key()==Qt::Key_6||ev->key()==Qt::Key_Down||ev->key()==Qt::Key_Up
                 ))
        return ;
    else if((N==2)&&(ev->key()==Qt::Key_D||ev->key()==Qt::Key_A||ev->key()==Qt::Key_W||ev->key()==Qt::Key_S||ev->key()==Qt::Key_F
                        ||ev->key()==Qt::Key_R||ev->key()==Qt::Key_Z||ev->key()==Qt::Key_X||ev->key()==Qt::Key_Q||ev->key()==Qt::Key_E
                 ))
        return ;
    if(ev->key()==Qt::Key_D)
    {
        qDebug()<<"d";
        hero.Movexy=MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero.Freeskill) //播放技能时候不播放动作
            if(hero.Movie.fileName()!=hero.Herogiffile[Righ]||!ev->isAutoRepeat())//不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {

                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Righ]);//gif存到movie 里

            }

    }
    else if(ev->key()==Qt::Key_A)
    {
        qDebug()<<"A";
        hero.Movexy=-MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Lef]||!ev->isAutoRepeat()) //不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Lef]);  //gif存到movie 里
                // hero.Movie.start();

            }
    }
    else if(ev->key()==Qt::Key_W&&hero.Xy.y==HEROlefty)//跳跃，只能一段跳
    {
        qDebug()<<"W";
        hero.Jump=JUMPstrart;

        hero.Movie.stop();
        hero.Movie.setFileName(hero.Herogiffile[To]);  //gif存到movie 里
            //  qDebug()<<hero.Herogiffile[Top];

    }
    else if(ev->key()==Qt::Key_S&&hero.Xy.y==HEROlefty)//蹲下
    {
        qDebug()<<"S";
            //if(hero.Movie.currentFrameNumber()==1) hero.Movie.stop();
        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Dow]||!ev->isAutoRepeat())
            {

                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Dow]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }

    else if(ev->key()==Qt::Key_Q)//1
    {
        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Qq]||!ev->isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Qq]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_E)//2
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Ee]||!ev->isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Ee]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_F)//3
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Ff]||!ev->isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Ff]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_R)//4
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Rr]||!ev->isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Rr]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_Z)//5
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Zz]||!ev->isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Zz]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_X)//6
    {

        if( !hero.Freeskill)
            if(hero.Movie.fileName()!=hero.Herogiffile[Xx]||!ev->isAutoRepeat())
            {
                hero.Freeskill=1;
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Xx]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_Right)
    {
        qDebug()<<"d";
        hero2.Movexy=MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero2.Freeskill) //播放技能时候不播放动作
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Righ]||!ev->isAutoRepeat())//不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {

                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Righ]);//gif存到movie 里

            }

    }
    else if(ev->key()==Qt::Key_Left)
    {
        qDebug()<<"A";
        hero2.Movexy=-MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Lef]||!ev->isAutoRepeat()) //不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Lef]);  //gif存到movie 里
                // hero.Movie.start();

            }
    }
    else if(ev->key()==Qt::Key_Up&&hero2.Xy.y==HEROlefty)//跳跃，只能一段跳
    {
        qDebug()<<"W";
        hero2.Jump=JUMPstrart;

        hero2.Movie.stop();
        hero2.Movie.setFileName(hero2.Herogiffile[To]);  //gif存到movie 里
            //  qDebug()<<hero.Herogiffile[Top];

    }
    else if(ev->key()==Qt::Key_Down&&hero2.Xy.y==HEROlefty)//蹲下
    {
        qDebug()<<"S";
            //if(hero.Movie.currentFrameNumber()==1) hero.Movie.stop();
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Dow]||!ev->isAutoRepeat())
            {

                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Dow]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }

    else if(ev->key()==Qt::Key_1)
    {
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Qq]||!ev->isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Qq]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_2)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Ee]||!ev->isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Ee]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_3)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Ff]||!ev->isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Ff]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_4)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Rr]||!ev->isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Rr]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_5)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Zz]||!ev->isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Zz]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(ev->key()==Qt::Key_6)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Xx]||!ev->isAutoRepeat())
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Xx]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }

}
void Udp_game::keyReleaseEvent(QKeyEvent *ev)//键盘松开
{
    if(N==1&&(ev->key()==Qt::Key_D||ev->key()==Qt::Key_A||ev->key()==Qt::Key_W||ev->key()==Qt::Key_S||ev->key()==Qt::Key_F
                   ||ev->key()==Qt::Key_R||ev->key()==Qt::Key_Z||ev->key()==Qt::Key_X||ev->key()==Qt::Key_Q||ev->key()==Qt::Key_E
                   ))
    {
        QString p1;
        if(ev->isAutoRepeat()) p1="R1";
        else p1="R0";
        p1=p1+QString::number(ev->key());
        socket->writeDatagram(p1.toUtf8(),sizeof(p1),QHostAddress(IP),port);
    }
    else if(N==2&&(ev->key()==Qt::Key_Left||ev->key()==Qt::Key_Right||ev->key()==Qt::Key_1||ev->key()==Qt::Key_2||ev->key()==Qt::Key_3
                        ||ev->key()==Qt::Key_4||ev->key()==Qt::Key_5||ev->key()==Qt::Key_6||ev->key()==Qt::Key_Down||ev->key()==Qt::Key_Up
                        ))
    {
        QString p1;
        if(ev->isAutoRepeat()) p1="R1";
        else p1="R0";
        p1=p1+QString::number(ev->key());
        socket->writeDatagram(p1.toUtf8(),sizeof(p1),QHostAddress(IP),port);
    }
    else if(N==1&&(ev->key()==Qt::Key_Left||ev->key()==Qt::Key_Right||ev->key()==Qt::Key_1||ev->key()==Qt::Key_2||ev->key()==Qt::Key_3
                        ||ev->key()==Qt::Key_4||ev->key()==Qt::Key_5||ev->key()==Qt::Key_6||ev->key()==Qt::Key_Down||ev->key()==Qt::Key_Up
                        ))
        return ;
    else if(N==2&&(ev->key()==Qt::Key_D||ev->key()==Qt::Key_A||ev->key()==Qt::Key_W||ev->key()==Qt::Key_S||ev->key()==Qt::Key_F
                        ||ev->key()==Qt::Key_R||ev->key()==Qt::Key_Z||ev->key()==Qt::Key_X||ev->key()==Qt::Key_Q||ev->key()==Qt::Key_E
                        ))
        return ;

    if(ev->key()==Qt::Key_D)
    {

        if(!ev->isAutoRepeat())//按下起来
        {
            hero.Movexy=0;
            initScence();

        }

    }
    else if(ev->key()==Qt::Key_A)
    {
        if(!ev->isAutoRepeat())//按下起来
        {
            hero.Movexy=0;
            initScence();
        }

    }
    else if(ev->key()==Qt::Key_S)
    {
        if(!ev->isAutoRepeat())//按下起来
        {
            initScence();
        }

    }
    else if(ev->key()==Qt::Key_W)
    {

        if(!ev->isAutoRepeat())//按下起来
        {
            initScence();
        }

    }
    else if(ev->key()==Qt::Key_Q)
    {
        if(!ev->isAutoRepeat()&&(!hero.Freeskill) )//按下起来
        {
            initScence();
        }
    }
    else if(ev->key()==Qt::Key_E)
    {
        if(!ev->isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev->key()==Qt::Key_F)
    {
        if(!ev->isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev->key()==Qt::Key_R)
    {
        if(!ev->isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev->key()==Qt::Key_Z)
    {
        if(!ev->isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev->key()==Qt::Key_X)
    {
        if(!ev->isAutoRepeat()&&(!hero.Freeskill))//按下起来
        {
            initScence();
        }
    }
    else if(ev->key()==Qt::Key_Right)
    {

        if(!ev->isAutoRepeat())//按下起来
        {
            hero2.Movexy=0;
            initScence2();

        }

    }
    else if(ev->key()==Qt::Key_Left)
    {
        if(!ev->isAutoRepeat())//按下起来
        {
            hero2.Movexy=0;
            initScence2();
        }

    }
    else if(ev->key()==Qt::Key_Down)
    {
        if(!ev->isAutoRepeat())//按下起来
        {
            initScence2();
        }

    }
    else if(ev->key()==Qt::Key_Up)
    {

        if(!ev->isAutoRepeat())//按下起来
        {
            initScence2();
        }

    }
    else if(ev->key()==Qt::Key_1)
    {
        if(!ev->isAutoRepeat()&&(!hero2.Freeskill) )
        {
            initScence2();
        }
    }
    else if(ev->key()==Qt::Key_2)
    {
        if(!ev->isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }
    else if(ev->key()==Qt::Key_3)
    {
        if(!ev->isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }
    else if(ev->key()==Qt::Key_4)
    {
        if(!ev->isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }
    else if(ev->key()==Qt::Key_5)
    {
        if(!ev->isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }
    else if(ev->key()==Qt::Key_6)
    {
        if(!ev->isAutoRepeat()&&(!hero2.Freeskill))//按下起来
        {
            initScence2();
        }
    }

    return;
}
