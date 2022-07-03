#ifndef HERORES_H
#define HERORES_H
//初始化
#include"GAME_define.h"

class HERORES/********************技能伤害 速度 x，y  大小w h***/
{
public:
    int number;//人物编号
    double hurt;//技能伤害
    int x;//速度
    int y;
    int w;//宽高
    int h;
    static void Sethres(HERORES *hres);


};

#endif // HERORES_H
