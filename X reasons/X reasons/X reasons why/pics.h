#pragma once
#include<graphics.h>
#include<conio.h>
#define WIDTH 960
#define HEIGHT 720

IMAGE img[50];// variable for the image
IMAGE mainpage;
IMAGE help;
TCHAR imagename[50];
//load the pics
void loadpic() {
	for (int i = 1; i <= 10; i++) {
		_stprintf_s(imagename, _T("../Image/Story/story%d.png"), i);
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
}

//put the image into the screen
void showpic(int i) {
	putimage(0, 0, &img[i]);
}

void helppage() {
	loadimage(&help, L"../Image/help.jpg", WIDTH, HEIGHT);
	putimage(0, 0, &help);
}