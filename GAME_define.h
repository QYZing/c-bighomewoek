#ifndef GAME_DEFINE_H
#define GAME_DEFINE_H
/**************游戏资源***********/

#define WINwidth 1250//主窗口宽度
#define WINheight 700//主窗口高度
#define LIFE 100//游戏生命
#define LIFEw 400//生命进度条宽
#define LIFEh  30
#define FRAMENUMBER 40//游戏总帧数
#define FRAMEHERO   200//人物总帧数
#define HERONUMBER  5//游戏英雄人物数

#define UI ":/res/ui0.png"
#define MA   ":/res/ma0.jpg"
#define START ":/res/S2.gif"
#define STARTmus ":/res/mus0.wav"
#define Sound    ":/res/Sound0.wav"
#define KOSound ":/res/KO.wav"
#define START1 ":res/S1.gif"
#define START0 ":res/S0.gif"
#define Map_res ":/res/1.png"
#define Map_res1 ":/res/.png"
#define Map_res2    ":/res/.gif"
#define Map_res3   ":/res/A.gif"
#define Map_res4  ":/res/B.gif"
#define KOmap ":/res/KO1.png"
//八神

#define JUMPMAX   200//跳最大高度
#define JUMPstrart 90//跳初速度
#define JUMPx   20//跳的减小值
#define MOVEx 20 //人物移动距离

#define HEROwidth 150//人物宽度
#define HEROheight 350//人物正常高度
#define HEROdownheight  180//人物蹲下高度
#define HEROdowny 520//蹲下位置

#define HEROleftx 100//人物位置左边
#define HEROlefty 350//人物位置
#define HEROrightx 1000//人物位置左边
#define HEROrighty 350//人物位置

/***************游戏动作对应基础增加的图片数*******/
#define Base  0

#define To 1
#define Dow 2
#define Lef 3
#define Righ 4
//普通攻击
#define Qq 5
#define Ee 6
#define Ff 7
#define Rr 8
#define Zz 9
#define Xx 10

#endif // GAME_DEFINE_H
