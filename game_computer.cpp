#include "game_computer.h"
#include "ui_game_computer.h"
#include"game_base.h"
#include<QKeyEvent>
#include<QPainter>
#include<QColor>
#include<QDebug>
#include<QLabel>
#include<QKeyEvent>

GAME_computer::GAME_computer(int lefthero,int righthero,QWidget *parent )
    :GAME_main( lefthero, righthero, parent)
    ,ui(new Ui::GAME_computer)
{
    playgame();
}

GAME_computer::~GAME_computer()
{
    delete ui;
}

void GAME_computer::playgame()//开始游戏
{
    // qDebug()<<1;
    WINtimer.start();//相当于循环
    connect(&WINtimer,&QTimer::timeout,this,[=](){//接受定时器发送信号

        /*********************和用户有关的变量更新************************/
        //按键自动调用
        /**********************************************************************/

        /******************生命值,位置的更新*************************/
        Computer(Comcontral());//电脑处理
        qDebug()<<"-----------------------------------------"<<Comcontral();
        updateinput(hero,hero2);//用户交互
        updateinput(hero2,hero);//用户交互
        updateagain();  //显示人物画面
        if(hero.Life<=0||hero2.Life<=0)
        {
            music->stop();
            hero.Movie.stop();
            hero2.Movie.stop();
            emit this->Close();
            WINtimer.stop();
            hero.Life=1;
            hero2.Life=1;
        }/*/////////////////////////////////////////----------------------------------/////////结束*/



    });


}


void GAME_computer::Computer(int t)//电脑操作
{

    if(t==2)
    {
        qDebug()<<"d";
        hero2.Movexy=MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero2.Freeskill) //播放技能时候不播放动作
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Righ])//不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {

                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Righ]);//gif存到movie 里

            }

    }
    else if(t==3)
    {
        qDebug()<<"A";
        hero2.Movexy=-MOVEx;
        /****加载gif 路径需要优化****/
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Lef]) //不是长按在更新gif图片,且上一次如果不是这个路径可以运行
            {
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Lef]);  //gif存到movie 里
                // hero.Movie.start();

            }
    }
    else if(t==0&&hero2.Xy.y==HEROlefty)//跳跃，只能一段跳
    {
        qDebug()<<"W";
        hero2.Jump=JUMPstrart;

        hero2.Movie.stop();
        hero2.Movie.setFileName(hero2.Herogiffile[To]);  //gif存到movie 里
            //  qDebug()<<hero.Herogiffile[Top];

    }
    else if(t==1&&hero2.Xy.y==HEROlefty)//蹲下
    {
        qDebug()<<"S";
            //if(hero.Movie.currentFrameNumber()==1) hero.Movie.stop();
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Dow])
            {

                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Dow]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }

    else if(t==4)
    {
        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Qq])
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Qq]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(t==5)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Ee])
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Ee]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(t==6)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Ff])
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Ff]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(t==7)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Rr])
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Rr]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(t==8)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Zz])
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Zz]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }
    else if(t==9)
    {

        if( !hero2.Freeskill)
            if(hero2.Movie.fileName()!=hero2.Herogiffile[Xx])
            {
                hero2.Freeskill=1;
                hero2.Movie.stop();
                hero2.Movie.setFileName(hero2.Herogiffile[Xx]);  //gif存到movie 里
                    //    qDebug()<<hero.Herogiffile[Down];
            }
    }

}

int GAME_computer::Comcontral()  //电脑返回值
{
    if(hero.Freeskill&&hero.Xy.x<hero2.Xy.x) return 2;
    else if(hero.Freeskill&&hero.Xy.x>hero2.Xy.x) return 3;
    if(hero.rect.intersects(QRect(hero2.Xy.x,hero2.Xy.y,HEROwidth,HEROheight))&&hero.Life>50)
    {
        return 6;
    }
    else if(hero.rect.intersects(QRect(hero2.Xy.x,hero2.Xy.y,HEROwidth,HEROheight))&&hero.Life>40)
    {
        return 7;
    }
    else if(hero.rect.intersects(QRect(hero2.Xy.x,hero2.Xy.y,HEROwidth,HEROheight))&&hero.Life>0)
    {
        return 9;
    }
    else if(hero.Xy.x<hero2.Xy.x) return 3;
    else if(hero.Xy.x>hero2.Xy.x) return 2;
    else return 0;
}


/*********************************好麻烦的bug好多********************************************/
/*///////////////////////键盘返回值是int值*/
void GAME_computer::keyPressEvent(QKeyEvent * ev)//键盘按下  因为有功能改变重写
{

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
            }
    }
}
void GAME_computer::keyReleaseEvent(QKeyEvent *ev)//键盘松开
{

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
    return;
}
