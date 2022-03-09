#include<graphics.h>
#include<conio.h>
#include <iostream>
#include"pics.h"
#define WIDTH 960
#define HEIGHT 720

ExMessage m;

void loadpic();
void showpic(int x);
void startpage();
void loadgame();
bool flag = true;


int main() {
	initgraph(WIDTH, HEIGHT);
	startpage();
	loadgame();

	closegraph();
	return 0;
}

//come into the start page
void startpage() {
	loadimage(&mainpage, L"../Image/start.png", WIDTH, HEIGHT);
	loadpic();
	while (flag) {
		m = getmessage(EM_MOUSE | EM_KEY);
		
		//written by yuxiao 08/03/2022 18:13
		putimage(0, 0, &mainpage);
		settextcolor(WHITE);
		settextstyle(40, 0, L"Gill Sans Ultra Bold");
		outtextxy(385, 395, L"Start Game");
		outtextxy(440, 445, L"Help");
		outtextxy(440, 495, L"Quit");

		switch (m.message) {

		//action done when player clicks the button
		case WM_LBUTTONDOWN:
			if (m.x >= 385 && m.x <= 575 && m.y >= 400 && m.y <= 435) { //start
				goto exitloop;
			}
			else if (m.x >= 440 && m.x <= 520 && m.y >= 445 && m.y <= 480) { //help
				helppage();
				(void)_getch();
				continue;//goes back to start page
			}
			else if (m.x >= 440 && m.x <= 519 && m.y >= 495 && m.y <= 530) { // quit
				exit(0);
			}
			break;

		//written by yuxiao 08/03/2022 18:13
		//hover animation
		case WM_MOUSEMOVE:
			if (m.x >= 385 && m.x <= 575 && m.y >= 400 && m.y <= 435) {//start
				settextcolor(YELLOW);
				outtextxy(385, 395, L"Start Game");
			}
			else if (m.x >= 440 && m.x <= 520 && m.y >= 445 && m.y <= 480) {//help
				settextcolor(YELLOW);
				outtextxy(440, 445, L"Help");
			}
			else if (m.x >= 440 && m.x <= 519 && m.y >= 495 && m.y <= 530) {//quit
				settextcolor(YELLOW);
				outtextxy(440, 495, L"Quit");
			}
		}

	}
	exitloop: ;// exits the loop
}

//after the start page
//load the game
void loadgame() {
	int page = 1;
	while (flag) {
		m = getmessage(EM_MOUSE | EM_KEY);
		loadpic();
		showpic(page);
		if (m.message == WM_LBUTTONDOWN) {
			page++;//go to next page if player leftclick
		}
	}
}
