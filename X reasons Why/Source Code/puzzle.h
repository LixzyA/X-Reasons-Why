#pragma once
#include <stdio.h>
#include <conio.h>  
#include <time.h>
#include <math.h>
#include <graphics.h>
#define  _CRT_SECURE_NO_WARNINGS

#define  PicLen  3  
#define  MapLen (PicLen+2) 
#define  Blank_Map -1  
#define  Len_Image  240


extern int  dx[4];
extern int  dy[4];
extern int Zero_pos[2];
extern int res;


int Dir(int x, int y);
void CreateMap();
void ShowMap();
int LOCAL_XY(double pos);
void Button();
void Mouse();
void judge();
void StartPuzzle();