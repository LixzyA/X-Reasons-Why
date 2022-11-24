#include "minesweeper.h"

//written by yuxiao
 int grahight = 415;//实际画布高
 int grawidth = 340;//实际画布宽
 int hight = 10;//实际游戏区域大小
 int width = 1;//实际游戏区域大小
 int times = 0;//获取总时间
 int time1 = 0, time2 = 0, time3 = 0;//记录时间的三位
 int first = 1;//判断第一次点击
 int bomb = 45;//炸弹数量
 int runing = 1;//是否结束游戏
 int smiles = 0;//笑脸图的变化
 int ture = 1;//判断是否开始游戏
 int choice = 0;
 int a = 1;//不让它一直弹出胜利的框
 int map[allhight + 2][allwidth + 2] = { 0 };//布局战场都出的两行和两个列用来辅助找出周围炸弹数
 int numbombs = 0;//炸弹第一位数
 int numbombss = 0;//炸弹第二位数
 int win = 0;//判断是否赢
 bool mflag = true;


void printfmaps()
{
	for (int i = 1; i <= hight; i++)
	{
		//printf("第%d行：", i);
		for (int j = 1; j <= width; j++)
		{

			int a = (j - 1) * 20;
			int b = (i - 1) * 20 + 72;
			printf("%3d", map[i][j]);

		}
		printf("\n");
	}
}
//输出后台数据看炸弹在哪，外挂！！！！！
void before();

void updategame()
{
	srand((unsigned int)time(NULL));
	int n = 0;
	while (n < bomb)
	{
		int x = rand() % hight + 1;
		int y = rand() % width + 1;
		if (map[x][y] == 0 && x != 0 && y != 0)
		{
			map[x][y] = -1;
			n++;
		}
	}
	//布置地雷
	for (int i = 1; i <= hight; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			if (map[i][j] == 0)
			{
				int sign = 0;
				sign = findbomb(i, j);
				map[i][j] = sign;
			}
		}
	}
	//查找不是雷的区域周围的雷数
	for (int i = 1; i <= hight; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			map[i][j] += 20;
		}
	}
	//加密
}
int findbomb(int a, int b)
{
	int all = 0;
	for (int i = a - 1; i <= a + 1; i++)
	{
		for (int j = b - 1; j <= b + 1; j++)
		{
			if (map[i][j] == -1)
			{
				all++;
			}
		}
	}
	return all;
}

void openzero(int m, int n)
{
	map[m][n] -= 20;//打开本身
	win++;
	for (int i = m - 1; i <= m + 1; i++)
	{
		for (int j = n - 1; j <= n + 1; j++)
		{
			if (i >= 1 && i <= width && j >= 1 && j <= hight)//保证在游戏区
			{
				if (map[i][j] <= 28 && map[i][j] >= 19)//保证没有翻开
				{
					if (map[i][j] != 20)//保证不是0
					{
						map[i][j] -= 20;
						win++;
					}
					else
						openzero(i, j);//递归

				}
			}
		}
	}
}
void newgame()
{
	for (int i = 1; i <= hight; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			map[i][j] = 0;
		}

	}
	updategame();

}
void whitchtouth()
{
	MOUSEMSG msg = GetMouseMsg();
	int x = msg.x;
	int y = msg.y;
	switch (msg.uMsg)
	{
	case  WM_LBUTTONDOWN:
		if (x >= 80 && x <= 250 && y >= 50 && y <= 120)
		{
			ture = 0;
			mflag = false;
			cleardevice();
			hight = 17;
			width = 17;
			grahight = 415;
			grawidth = 340;
			bomb = 20;
		}
		if (x >= 80 && x <= 250 && y >= 150 && y <= 220) {
			ture = 0;
			choice = 1;
		}
		break;

	}

}

void whitchtouth2() {
	ExMessage m;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case  WM_LBUTTONDOWN:
		choice = 0;
		ture = 1;
		break;

	}
}
void showbomb()
{
	int i, j;
	for (i = 1; i <= hight; i++)
	{
		for (j = 1; j <= width; j++)
		{
			if (map[i][j] == 19)
			{
				map[i][j] -= 20;
			}
		}
	}
}

void before()
{
	for (int i = 1; i <= hight; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			map[i][j] = 0;
		}

	}
	ture = 1;//重置参数
	first = 1;
	smiles = 0;
	runing = 1;
	win = 0;
	a = 1;
	system("cls");
	initgraph(340, 415);
	setbkcolor(RGB(189, 189, 189));
	cleardevice();
	//准备过程
	while (ture)
	{
		settextcolor(BLACK);
		settextstyle(40, 0, L"Arial");
		rectangle(80, 50, 250, 120);
		outtextxy(130, 65, L"Play");
		whitchtouth();

	}
	cleardevice();
	initgraph(grawidth, grahight);
	setbkcolor(RGB(189, 189, 189));
	cleardevice();
	//开始
	numbombss = bomb % 10;
	numbombs = bomb / 10;
	updategame();
	printfmaps();
}