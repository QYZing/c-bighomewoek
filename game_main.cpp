#include "game_main.h"
#include "ui_game_main.h"

#include<QKeyEvent>
#include<QPainter>
#include<QColor>
#include<QDebug>
#include<QLabel>
#include<QKeyEvent>
#include"ma.h"
//vector<HERORES> HEROres;//存全英雄路径的

GAME_main::GAME_main(int lefthero,int righthero,QWidget *parent )
    : QWidget(parent),heroleft(lefthero),heroright(righthero)
    ,ui(new Ui::GAME_main)
{

    ui->setupUi(this);
    this->setWindowTitle("拳皇01");
    this->setFixedSize(WINwidth,WINheight);
    WINtimer.setInterval(FRAMENUMBER);//帧数
    map.load(Map_res);//背景地图加载

    music=new QSoundEffect(this);
    music->setSource(QUrl::fromLocalFile(Sound));
    music->setLoopCount(QSoundEffect::Infinite);
    music->setVolume(0.1f);
    music->play();

    HERORES::Sethres(hres);//英雄主文件技能伤害速度绑定
    this->grabKeyboard();

    hero.input(heroleft,hres,0);//英雄基类用语选英雄/*******************************选英雄接口**********/
    hero.lr=0;
    ui->leftlife->setFixedSize(LIFEw,LIFEh);//尺寸
    ui->leftlife->setRange(0,LIFE);//
    ui->leftlife->setValue(hero.Life);//生命
    ui->leftlife->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{background:RED}");
    ui->Heroleft->setScaledContents(1);
    ui->Heroleft->setGeometry(hero.rect);//设置ui控件位置
    hero.rect.setRect(hero.Xy.x,hero.Xy.y,HEROwidth,HEROheight);//人物矩形框


    hero2.input(heroright,hres,1);
    hero2.lr=1;
    ui->rightlife->setFixedSize(LIFEw,LIFEh);
    ui->rightlife->setRange(0,LIFE);
    ui->rightlife->setValue(hero2.Life);
    ui->rightlife->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{background:RED}");
    hero2.Xy.x=HEROrightx;  hero2.Xy.y=HEROrighty;//需要重新设置一下
    hero2.rect.setRect(hero2.Xy.x,hero2.Xy.y,HEROwidth,HEROheight);//人物矩形框
    ui->Heroright->setScaledContents(1);
    ui->Heroright->setGeometry(hero2.rect);//设置ui控件位置

    initScence();//初始化
    initScence2();//初始化
    playgame();
}

GAME_main::~GAME_main()
{
    delete ui;
}

void GAME_main::initScence()//初始化
{

      if( !hero.Freeskill)
      {
         hero.Movie.stop();
         ui->Heroleft->setGeometry(hero.rect);//设置ui控件位置
         hero.Movie.setFileName(hero.Herogiffile[Base]);
         QSize Size(ui->Heroleft->width(),ui->Heroleft->height());//设置gif以及Qlabel尺寸
         hero.Movie.setScaledSize(Size);//设置gif尺寸
         hero.Movie.start();
         ui->Heroleft->setMovie(&hero.Movie);//把Movie加载到QLabel中
      }


}
void GAME_main::initScence2()//初始化
{
    if( !hero2.Freeskill)
    {
        hero2.Movie.stop();
        ui->Heroright->setGeometry(hero2.rect);//设置ui控件位置
        hero2.Movie.setFileName(hero2.Herogiffile[Base]);
        QSize Size(ui->Heroright->width(),ui->Heroright->height());//设置gif以及Qlabel尺寸
        hero2.Movie.setScaledSize(Size);//设置gif尺寸
        hero2.Movie.start();
        ui->Heroright->setMovie(&hero2.Movie);//把Movie加载到QLabel中
    }
}
void GAME_main::playgame()//开始游戏
{
   // qDebug()<<1;
    WINtimer.start();//相当于循环
    connect(&WINtimer,&QTimer::timeout,this,[=](){//接受定时器发送信号

     /*********************和用户有关的变量更新************************/
       //按键自动调用
      /**********************************************************************/

     /******************生命值,位置的更新*************************/
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
void GAME_main::updateinput(GAME_base &hero,GAME_base &hero2)//用户交互
{


/*//////////////////////////////和用户无关的事件更新///////////////////////////////////////////////////////////////////////////////*/


     if(hero.Freeskill) //技能释放完回到初状态
     {

       if(hero.Movie.frameCount()==hero.Movie.currentFrameNumber()+1)
       {
                              qDebug()<<"12222222222222222222222222222222222222222222222";
             hero.Freeskill=0;
        if(hero.lr)
               initScence2();
        else
               initScence();
       }
     }
     /***********************跳的事件***  竖直方向上  *************************/
     if(hero.Jump!=0)
     {
        if(hero.Jump>=0||hero.Xy.y!=HEROlefty)//跳跃  改位置
        {
            hero.Xy.y-=hero.Jump;
            hero.Jump-=JUMPx;
        }
        if(hero.Jump<0&&hero.Xy.y==HEROlefty)
        {

            hero.Jump=0;//跳跃
            if(hero.Movexy>0)
            {
                hero.Movie.stop();//换图片必须让上一张停止
                hero.Movie.setFileName(hero.Herogiffile[Righ]);//gif存到movie 里
            }
            else if(hero.Movexy<0)
            {
                hero.Movie.stop();
                hero.Movie.setFileName(hero.Herogiffile[Lef]);//gif存到movie 里
            }
            else {
                if(hero.lr)
                    initScence2();
                else
                    initScence();
            }

        }
     }
     /**********************跑和走的事件***    水平方向上*************************/
     if(hero.Movexy!=0)
     {
         if(hero.Movexy>0&& hero.Xy.x<=WINwidth-HEROwidth) hero.Xy.x+=hero.Movexy;
         else if(hero.Movexy<0&&hero.Xy.x>=MOVEx) hero.Xy.x+=hero.Movexy;
     }



     if(hero.Movie.fileName()==hero.Herogiffile[Dow])  //蹲特例
     {
         hero.rect.setRect(hero.Xy.x,hero.Xy.y+110,HEROwidth,HEROheight-110);//更新用户坐标数据//设置ui控件y位置
     }
     else if(hero.Movie.fileName()==hero.Herogiffile[Ee])//2
     {
         if(hero.lr)
            hero.rect.setRect(hero.Xy.x-110,hero.Xy.y-20,HEROwidth+110,HEROheight+20);//更新用户坐标数据
         else
             hero.rect.setRect(hero.Xy.x,hero.Xy.y-20,HEROwidth+110,HEROheight+20);//更新用户坐标数据
     }
     else if(hero.Movie.fileName()==hero.Herogiffile[Qq])//1
     {
         if(hero.lr)
             hero.rect.setRect(hero.Xy.x-40,hero.Xy.y-HEROheight,HEROwidth+100,HEROheight+HEROheight);//更新用户坐标数据
         else
             hero.rect.setRect(hero.Xy.x-40,hero.Xy.y-HEROheight/2,HEROwidth+100,HEROheight+HEROheight/2);//更新用户坐标数据
     }
     else if(hero.Movie.fileName()==hero.Herogiffile[Ff])// 3
     {
        if(hero.lr)
              hero.rect.setRect(hero.Xy.x-hero.Skill[0].w,hero.Xy.y-hero.Skill[0].h,HEROwidth+hero.Skill[0].w,HEROheight+hero.Skill[0].h);//更新用户坐标数据
        else  hero.rect.setRect(hero.Xy.x,hero.Xy.y-hero.Skill[0].h,HEROwidth+hero.Skill[0].w,HEROheight+hero.Skill[0].h);//更新用户坐标数据
        if(hero.rect.intersects(QRect(hero2.Xy.x,hero2.Xy.y,HEROwidth,HEROheight))) //计算碰撞
        {
            if(hero.Skill[0].Hurt>0)
            {
                hero2.Life-=hero.Skill[0].Hurt;
            }
             else hero.Life-=hero.Skill[1].Hurt;
                         qDebug()<<hero.Life<<" "<<hero2.Life;
        }
     }
     else if(hero.Movie.fileName()==hero.Herogiffile[Rr])// 4
     {
      if(hero.lr)
         hero.rect.setRect(hero.Xy.x-hero.Skill[1].w,hero.Xy.y-hero.Skill[1].h, HEROwidth+hero.Skill[1].w, HEROheight+hero.Skill[1].h);//更新用户坐标数据
      else
          hero.rect.setRect(hero.Xy.x,hero.Xy.y-hero.Skill[1].h, HEROwidth+hero.Skill[1].w, HEROheight+hero.Skill[1].h);//更新用户坐标数据
       //计算碰撞
      if(hero.rect.intersects(QRect(hero2.Xy.x,hero2.Xy.y,HEROwidth,HEROheight)))
      {
          if(hero.Skill[1].Hurt>0)
          {
              hero2.Life-=hero.Skill[1].Hurt;
              hero.Skill[2].Hurt-=0.004;//大招技能会减少下一次伤害
          }
          else hero.Life-=hero.Skill[1].Hurt;
      }
     }
     else if(hero.Movie.fileName()==hero.Herogiffile[Zz])// 5
     {
      if(hero.lr)
         hero.rect.setRect(hero.Xy.x-hero.Skill[2].w,hero.Xy.y-hero.Skill[2].h, HEROwidth+hero.Skill[2].w, HEROheight+hero.Skill[2].h);//更新用户坐标数据
      else
         hero.rect.setRect(hero.Xy.x,hero.Xy.y-hero.Skill[2].h, HEROwidth+hero.Skill[2].w, HEROheight+hero.Skill[2].h);//更新用户坐标数据
      //计算碰撞
      if(hero.rect.intersects(QRect(hero2.Xy.x,hero2.Xy.y,HEROwidth,HEROheight)))
      {
          if(hero.Skill[2].Hurt>0)
          {
              hero2.Life-=hero.Skill[2].Hurt;
              hero.Skill[2].Hurt-=0.005;
          }
          else hero.Life-=hero.Skill[2].Hurt;
      }
     }
     else if(hero.Movie.fileName()==hero.Herogiffile[Xx])// 6
     {
       if(hero.lr)
           hero.rect.setRect(hero.Xy.x-hero.Skill[3].w,hero.Xy.y-hero.Skill[3].h, HEROwidth+hero.Skill[3].w, HEROheight+hero.Skill[3].h);//更新用户坐标数据
        else
           hero.rect.setRect(hero.Xy.x,hero.Xy.y-hero.Skill[3].h, HEROwidth+hero.Skill[3].w, HEROheight+hero.Skill[3].h);//更新用户坐标数据
        if(hero.rect.intersects(QRect(hero2.Xy.x,hero2.Xy.y,HEROwidth,HEROheight))) //计算碰撞
        {
            if(hero.Skill[3].Hurt>0)
            {
                hero2.Life-=hero.Skill[3].Hurt;
            }
            else hero.Life-=hero.Skill[3].Hurt;
        }

     }
     else
     {
         hero.rect.setRect(hero.Xy.x,hero.Xy.y,HEROwidth+50,HEROheight);//更新用户坐标数据
     }


}

void GAME_main::paintEvent(QPaintEvent *)//画图
{
    QPainter painter(this);
    painter.drawPixmap(0,0,WINwidth,WINheight,map);
}
void GAME_main::updateagain()
{
    hero.Movie.start();
    ui->Heroleft->setMovie(&hero.Movie);
    ui->Heroleft->setGeometry(hero.rect);

    hero2.Movie.start();
    ui->Heroright->setMovie(&hero2.Movie);
    ui->Heroright->setGeometry(hero2.rect);
    //生命条改变
    ui->leftlife->setValue(hero.Life);
    ui->rightlife->setValue(hero2.Life);
}

/*********************************好麻烦的bug好多********************************************/
/*///////////////////////键盘返回值是int值*/
void GAME_main::keyPressEvent(QKeyEvent * ev)//键盘按下
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
void GAME_main::keyReleaseEvent(QKeyEvent *ev)//键盘松开
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
   if(ev->key()==Qt::Key_Right)
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
