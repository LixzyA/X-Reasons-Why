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
		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			if (m.x >= 385 && m.x <= 570 && m.y >= 400 && m.y <= 427)
				showpic(1);
			else if (m.x >= 420 && m.x <= 538 && m.y >= 440 && m.y <= 470)
				showpic(2);
			else if (m.x >= 440 && m.x <= 519 && m.y >= 490 && m.y <= 522)
				exit(0);

			break;
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