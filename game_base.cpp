#include "game_base.h"

#include<QDebug>
GAME_base::GAME_base()
{


    //void input();
     Life=LIFE;//生命
     lr=0;//默认不是
     Xy.x=HEROleftx;//位置
     Xy.y=HEROlefty;
     Jump=0;//初始化跳
     Movexy=0;//初始化水平速度

     Freeskill=0;  //发技能
     Attacked=0;//用于检测是否挨打

    //rect;//人物边框用于判断碰撞


};

void GAME_base::inint()
{

} 
void GAME_base:: input(int number,HERORES *hres,bool lr)//选英雄
{
     HEROnumber=number;
    int i=number;
    //0 base 1-4 w,s,a,d 5-6普攻 //7-8 2小技能 9-10大技能  11-19音效
    for(int o=0;o<=10;o++) //11张图片采用20进位 ,方便后续添加
    {
        QString t;
        if(lr)
        {

             t=Map_res4;
        }
        else
        {
             t=Map_res3;
        }
        QString t1=QString::number(i*20+o);
        t.insert(7,t1);
                  qDebug()<<o;
        if(o<=6) Herogiffile.push_back(t);//英雄基本动作存储图片
        else
        {
             Herogiffile.push_back(t);
             Skill[o-7].setbase(hres[i*4+o-7].hurt,hres[i*4+o-7].x,hres[i*4+o-7].y);
             Skill[o-7].Xy=Xy;
             Skill[o-7].rec.setRect(Xy.x,Xy.y,0, 0);
             Skill[o-7].w=hres[i*4+o-7].w;
             Skill[o-7].h=hres[i*4+o-7].h;
                    qDebug()<<"skill"<<hres[i*4+o-7].w;
                }//技能存储图片
    }

}
