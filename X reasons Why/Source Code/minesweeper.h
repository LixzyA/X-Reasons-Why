#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#define allhight 100//总数组大小
#define allwidth 100//总数组大小
extern int grahight;//实际画布高
extern int grawidth;//实际画布宽
extern int hight;//实际游戏区域大小
extern int width;//实际游戏区域大小
extern int times;//获取总时间
extern int time1, time2, time3;//记录时间的三位
extern int first;//判断第一次点击
extern int bomb;//炸弹数量
extern int runing;//是否结束游戏
extern int smiles;//笑脸图的变化
extern int ture;//判断是否开始游戏
extern int choice;
extern int a;//不让它一直弹出胜利的框
extern int map[allhight + 2][allwidth + 2];//布局战场都出的两行和两个列用来辅助找出周围炸弹数
extern int numbombs;//炸弹第一位数
extern int numbombss;//炸弹第二位数
extern int win;//判断是否赢
void printfmaps();
void updategame();//更新数据并且加密
int findbomb(int a, int b);//找正常方块附近的炸弹数量
void theloadimage();//加载图片
void newgame();//刷新游戏
void showbomb();//点击炸弹后显示所有炸弹
void openzero(int m, int n);//遇到空格打开，递归思想
void whitchtouth();//开始界面的选择函数
void whitchtouth2();
void before();
extern bool mflag;