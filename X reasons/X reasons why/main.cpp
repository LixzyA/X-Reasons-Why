#include<graphics.h>
#include<conio.h>
#include <iostream>
using namespace std;
#define WIDTH 960
#define HEIGHT 720

IMAGE img[50];// variable for the image
IMAGE mainpage;
TCHAR imagename[50];
ExMessage m;

void loadpic();
void showpic(int x);
void startgame();


int main() {
	initgraph(WIDTH, HEIGHT);
	startgame();
	

	_getch();
	closegraph();
	return 0;
}

//starts the game
void startgame() {
	loadimage(&mainpage, L"../Image/start.png", WIDTH, HEIGHT);
	putimage(0, 0, &mainpage);
	loadpic();
	while (true) {
		m = getmessage(EM_MOUSE | EM_KEY);

		if (m.x >= 385 && m.x <= 575 && m.y >= 400 && m.y <= 435) {
			setlinecolor(GREEN);
			rectangle(385, 400, 575, 435);
			if (m.message == WM_LBUTTONDOWN)
				showpic(1);
		}
		else if (m.x >= 440 && m.x <= 520 && m.y >= 450 && m.y <= 485)
		{
			setlinecolor(GREEN);
			rectangle(440, 450, 520, 485);
			if (m.message == WM_LBUTTONDOWN)
				showpic(2);
		}

		else if (m.x >= 440 && m.x <= 519 && m.y >= 500 && m.y <= 535) {
			setlinecolor(GREEN);
			rectangle(440, 500, 519, 535);
			if (m.message == WM_LBUTTONDOWN)
				exit(0);
		}
		else {
			setlinecolor(TRANSPARENT);
			rectangle(0, 0, 0, 0);
		}
	}
}

//load the pics
void loadpic() {
	for (int i = 1; i <= 5; i++) {
		_stprintf_s(imagename, _T("../Image/back%d.jpg"), i);
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
}

//put the image into the screen
void showpic(int i) {
	putimage(0, 0, &img[i]);
}