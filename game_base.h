    #ifndef GAME_BASE_H
#define GAME_BASE_H

#include<QPixmap>
#include<QRect>
#include<QTimer>
#include<iostream>
#include<QString>
#include<vector>
#include<QMovie>
#include"GAME_define.h"
#include"herores.h"
using namespace std;



struct pos
{
    int x,y;
};
class Skill
{
public:
    void setbase(double hur,int movx,int movy){
        Hurt=hur;
        Movex=movx;
        Movey=movy;
    }
  double Hurt;//伤害
  int Movex;//技能会自动移动 x轴
  int Movey;//y轴
  int w;//宽高
  int h;
  //QMovie Movie;//技能gif格式

  pos Xy;
  QRect rec;//技能方向框

};

class GAME_base
{
public:
    GAME_base();
    void input(int number,HERORES *hres,bool lr);
    void inint();
    double Life;//生命
    //还需要添加生血条

    bool lr;//判断是否右边人物
    pos Xy;//位置

    vector<QString> Herogiffile;//人物技能资源路径
    QMovie Movie;//加载人物资源
    int HEROnumber;//英雄编号
    Skill Skill[5]; //可以有多个技能

    int Jump;//跳跃速度记录值
    int Movexy;//水平速度记录值

    QRect rect;//人物边框用于判断碰撞
    bool Attacked;//用于检测是否挨打
    bool Freeskill;//检测是否在放技能

};

#endif // GAME_BASE_H
