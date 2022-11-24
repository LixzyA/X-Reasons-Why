#include<graphics.h>
#include<stdlib.h>
#include<assert.h>
#include<conio.h>
#include <iostream>
#include<cstdio>
#include <mmsystem.h>
#include<string.h>
#include "save.h"
#include"input.h"
#include"minesweeper.h"
#include"puzzle.h"
#pragma comment(lib, "Winmm.lib")//for sound and bgm
#define WIDTH 960
#define HEIGHT 720
#define BUFFER_SIZE 100

//variable declaration
IMAGE img[150];// variable for the image
IMAGE puzzleimg[PicLen * PicLen];
IMAGE puzzlehelp;
IMAGE mathProblem[5];
IMAGE mainpage;
IMAGE puzzleans;
IMAGE help;
IMAGE paused;
clock_t start_t, end_t;//开始实际时间，结束时间算时间差
IMAGE block[13];//1-8和空格和炸弹图片
IMAGE smile[4];//笑脸的各种状态
IMAGE numbomb[10];//时间图片
IMAGE minehelp;
TCHAR imagename[50];
TCHAR buffer[10];
wchar_t s[10];
int Map[MapLen][MapLen];
bool flag = true, pw = true, mineflag = true, puzzleflag = true;
int currentPage;
static int iteration1 = 1, iteration2 = 1;
static int minegame = 0, puzzlegame = 0;//0 = haven't played, 1= played
static int sound0 = 0;

//function declaration
void loadstory0();
void loadstory1();
void loadstory2();
void loadstory3();
void loadstory4();
void mathq();
void showmath(int);
void showpic(int i);
void helppage();
void pausepage(int currentPage);
void startpage();
void loadgame();
void opensound();
void minesweeper();
void printfmap();
void theloadimage();
void playmine();

//main function
int main() {
	initgraph(WIDTH, HEIGHT);
	loadstory0();
	startpage();
	loadgame();
	closegraph();
	return 0;
}

//written by felix 04/03
//come into the start page
void startpage() {
	loadimage(&mainpage, L"../Image/Others/start.png", WIDTH, HEIGHT);
	putimage(0, 0, &mainpage);

	if(iteration1 == 1){
		loadstory1();
		loadstory2();
		iteration1++;
	}
	
	
	BeginBatchDraw();
	while (flag) {
		getinput();

		//options
		//written by yuxiao 08/03/2022 18:13
		settextcolor(WHITE);
		settextstyle(40, 0, L"Gill Sans Ultra Bold");
		outtextxy(385, 395, L"Start Game");
		outtextxy(440, 445, L"Help");
		outtextxy(440, 495, L"Quit");
		EndBatchDraw();

		switch (m.message) {

			//action done when player clicks the button
		case WM_LBUTTONDOWN:
			if (m.x >= 385 && m.x <= 575 && m.y >= 400 && m.y <= 435) { //start
				return;//loads the actual game
			}
			else if (m.x >= 440 && m.x <= 520 && m.y >= 445 && m.y <= 480) { //help
				return helppage();//goes to help page
			}
			else if (m.x >= 440 && m.x <= 519 && m.y >= 495 && m.y <= 530) { // quit
				exit(0);//quits program
			}
			break;

			//written by yuxiao 08/03/2022 18:13
			//hover animation
		case WM_MOUSEMOVE:
			if (m.x >= 385 && m.x <= 575 && m.y >= 400 && m.y <= 435) {//start
				BeginBatchDraw();
				settextcolor(YELLOW);
				outtextxy(385, 395, L"Start Game");
				EndBatchDraw();
			}
			else if (m.x >= 440 && m.x <= 520 && m.y >= 445 && m.y <= 480) {//help
				BeginBatchDraw();
				settextcolor(YELLOW);
				outtextxy(440, 445, L"Help");
				EndBatchDraw();
			}
			else if (m.x >= 440 && m.x <= 519 && m.y >= 495 && m.y <= 530) {//quit
				BeginBatchDraw();
				settextcolor(YELLOW);
				outtextxy(440, 495, L"Quit");
				EndBatchDraw();
			}
		}

	}
}


//after the start page
//load the game
void loadgame() {
	
	//written by felix
	if (iteration2 == 1) {
		continuesave();
		loadstory3();
		loadstory4();
		currentPage = page;
		opensound();
		iteration2++;
	}
	if ((minegame || puzzlegame) == 1) {//returns screen size to normal
		initgraph(WIDTH, HEIGHT);
	}

	settextcolor(WHITE);
	settextstyle(48, 0, L"Agency FB", 0, 0, 600, 0, 0, 0);
	setbkmode(TRANSPARENT);
	int clicks1 = 0, clicks2 = 0, clicks3 = 0;

	while (flag) {
		//written by wang fang xu 16/03
		//plays the bgm and saves game
		if (currentPage >= 1 && currentPage <= 65) {//chapter 0
			mciSendString(_T("open bgm//bgm0.mp3 alias mymusic0"), NULL, 0, NULL);
			mciSendString(_T("play mymusic0 repeat"), NULL, 0, NULL);
		}
		else if (currentPage >= 66 && currentPage <= 94) {// chapter 1
			mciSendString(_T("close mymusic0"), NULL, 0, NULL);
			mciSendString(_T("open bgm//bgm1.mp3 alias mymusic1"), NULL, 0, NULL);
			mciSendString(_T("play mymusic1 repeat"), NULL, 0, NULL);
			chapter = 1;
			savegame();
		}
		else if (currentPage >= 95 && currentPage <= 101) {// chapter 2
			mciSendString(_T("close mymusic1"), NULL, 0, NULL);
			mciSendString(_T("open bgm//bgm2.mp3 alias mymusic2"), NULL, 0, NULL);
			mciSendString(_T("play mymusic2 repeat"), NULL, 0, NULL);
			chapter = 2;
			savegame();
		}
		else if (currentPage >= 102 && currentPage <= 130) {// chapter 3
			mciSendString(_T("close mymusic2"), NULL, 0, NULL);
			mciSendString(_T("open bgm//bgm3.mp3 alias mymusic3"), NULL, 0, NULL);
			mciSendString(_T("play mymusic3 repeat"), NULL, 0, NULL);
			chapter = 3;
			savegame();
		}
		else if (currentPage >= 131 && currentPage <= 138) {// chapter 4
			mciSendString(_T("close mymusic3"), NULL, 0, NULL);
			mciSendString(_T("open bgm//bgm4.mp3 alias mymusic4"), NULL, 0, NULL);
			mciSendString(_T("play mymusic4 repeat"), NULL, 0, NULL);
			chapter = 4;
			savegame();
		}

		//written by felix
		getinput();
		showpic(currentPage);
		switch (currentPage) {

		case 3:
			mciSendString(_T("play sound3"), NULL, 0, NULL);//message sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 13:
			//options
			BeginBatchDraw();
			outtextxy(350, 400, L"Yes");
			outtextxy(580, 400, L"No");
			FlushBatchDraw();
			
			if (m.message == WM_LBUTTONDOWN)
			{
				if (m.x >= 350 && m.x <= 400 && m.y >= 405 && m.y <= 450) //yes
				{
					currentPage++;
					break;
				}
				else if (m.x >= 580 && m.x <= 615 && m.y >= 405 && m.y <= 450) //no
				{
					int result1 = MessageBox(0, L"Are you sure you want to quit the game?", L"", MB_YESNO | MB_SYSTEMMODAL);
					if (result1 == IDYES) {
						exit(0);
						break;
					}
					else {
						int result2 = MessageBox(0, L"Do you want to play the game?", L"", MB_YESNO | MB_SYSTEMMODAL);
						if (!(result2 == IDYES)) {
							exit(0);
						}
					}
					currentPage++;
					break;
				}
				break;
			}

			break;

		case 14:
			BeginBatchDraw();
			outtextxy(200, 300, L"A. Go to Irene's home to comfort her sister");
			outtextxy(200, 390, L"B. Go around in school");
			FlushBatchDraw();
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 200 && m.x <= 780 && m.y >= 305 && m.y <= 395) //Option A goes to irene home
				{
					currentPage = 28;
					break;
				}
				else if (m.x >= 200 && m.x <= 510 && m.y >= 395 && m.y <= 440) //Option B go to school
				{
					currentPage++;
					break;
				}
			}
			break;

		case 15:
		case 16:
		case 17:
		case 18:
			Sleep(200);
			currentPage++;
			break;

		case 29:
			mciSendString(_T("play sound6"), NULL, 0, NULL);//knock sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 30:
			mciSendString(_T("play sound5"), NULL, 0, NULL);//opendoor sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 35:
			BeginBatchDraw();
			outtextxy(270, 494, L"A. I don't know ... Maybe.");
			outtextxy(270, 550, L"B. There are truly some bad discussions");
			outtextxy(270, 590, L" about her");
			FlushBatchDraw();

			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 270 && m.x <= 596 && m.y >= 494 && m.y <= 529) //Option A goes to next page
				{
					currentPage++;
					break;
				}
				else if ((m.x >= 270 && m.x <= 754 && m.y >= 550 && m.y <= 585) || (m.x >= 270 && m.x <= 636 && m.y >= 590 && m.y <= 625)) //Option B to page 43
				{
					currentPage = 43;
					break;
				}
			}
			break;

		case 42:
		case 53:
		case 58:
			if (m.message == WM_LBUTTONDOWN) {// goes to page 59
				currentPage = 59;
			}
			break;

		case 47:
			BeginBatchDraw();
			outtextxy(270, 500, L"A. I believe her");
			outtextxy(270, 590, L"B. Emmmmmm");
			FlushBatchDraw();
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 270 && m.x <= 470 && m.y >= 550 && m.y <= 590) //Option A goes to next page
				{
					currentPage++;
					break;
				}
				else if (m.x >= 270 && m.x <= 470 && m.y >= 600 && m.y <= 640) //Option B goes to page 54
				{
					currentPage = 54;
					break;
				}
			}
			break;

		case 60:
			mciSendString(_T("play sound1"), NULL, 0, NULL);//drawer sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;


		//id password
		case 62:
			while (pw) {
				size_t i;
				char* buffer1 = (char*)malloc(BUFFER_SIZE);
				InputBox(buffer, 5, L"Enter the password : ",L"Password",L"Enter a password",300,0,true);
				wcstombs_s(&i, buffer1, (size_t)BUFFER_SIZE, buffer, (size_t)BUFFER_SIZE - 1);//convert unicode to multibyte string
				int NumberOfTries = 1;
				
				while (strcmp(buffer1, "0224") != 0) {
					if (NumberOfTries < 3) {
						InputBox(buffer, 5, L"Wrong! Try again! \nEnter the password :\nHint : Please pay attention to Irene's ID", L"Password", L"Enter a password", 300, 0, true);
						wcstombs_s(&i, buffer1, (size_t)BUFFER_SIZE, buffer, (size_t)BUFFER_SIZE - 1);//convert unicode to multibyte string
					}
					else {
						InputBox(buffer, 5, L"Wrong! Try again! \nEnter the password :\nHint : Please pay attention to Irene's ID", 
							L"Password", L"Enter a password", 300, 0, true);
						wcstombs_s(&i, buffer1, (size_t)BUFFER_SIZE, buffer, (size_t)BUFFER_SIZE - 1);//convert unicode to multibyte string
					}
					NumberOfTries++;
				}
				pw = false;
			}
			currentPage++;
			break;		

		case 63:
			mciSendString(_T("play sound4"), NULL, 0, NULL);//unlock sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 68:
		case 103:
			if (sound0 == 0) {
				mciSendString(_T("play sound0"), NULL, 0, NULL);//page sfx
				sound0++;
			}
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 104:
			if (sound0 == 1) {
				mciSendString(_T("close sound0"), NULL, 0, NULL);
				mciSendString(_T("open sound//sound0_page.mp3 alias sound0"), NULL, 0, NULL);
				mciSendString(_T("play sound0"), NULL, 0, NULL);//page sfx
				sound0++;
			}
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 85:
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				mciSendString(_T("close mymusic1"), NULL, 0, NULL);
				minesweeper();//plays minesweeper
				break;
			}
			break;

		case 88:
			mciSendString(_T("play sound3"), NULL, 0, NULL);//message sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 89:
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 916 && m.x <= 941 && m.y >= 31 && m.y <= 45) {//goes to next page
					currentPage++;
					break;
				}
				clicks1++;
			}
			if (clicks1 >= 5 && clicks1 <= 6) {
				MessageBox(0, L"Click on specific parts of the screen to open the chat history!", L"Hint", MB_OK | MB_SYSTEMMODAL);
				clicks1 = 0;
			}
			break;

		case 90:
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 328 && m.x <= 928 && m.y >= 547 && m.y <= 603) {//goes to next page
					currentPage++;
					break;
				}
				clicks2++;
			}
			if (clicks2 >= 5 && clicks2 <= 6) {
				MessageBox(0, L"Click on specific parts of the screen to open the chat history!", L"Hint", MB_OK | MB_SYSTEMMODAL);
				clicks2 = 0;
			}
			break;

		case 91:
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 821 && m.x <= 843 && m.y >= 209 && m.y <= 222) {//goes to next page
					currentPage++;
					break;
				}
				clicks3++;
			}
			if (clicks3 >= 5 && clicks3 <= 6) {
				MessageBox(0, L"Click on specific parts of the screen to open the chat history!", L"Hint", MB_OK | MB_SYSTEMMODAL);
				clicks3 = 0;
			}
			break;

		case 98:
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				StartPuzzle();//plays puzzle
				break;
			}
			break;

		case 111:
			BeginBatchDraw();
			settextcolor(BLACK);
			settextstyle(48, 0, L"Agency FB", 0, 0, 800, 0, 0, 0);
			outtextxy(300, 550, L"A. Edwin");
			outtextxy(616, 550, L"B. Peter");
			FlushBatchDraw();
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 300 && m.x <= 413 && m.y >= 550 && m.y <= 590)//goes to edwin
				{
					currentPage++;
					break;
				}
				else if (m.x >= 616 && m.x <= 730 && m.y >= 550 && m.y <= 590)//goes to peter
				{
					currentPage= 115;
					break;
				}
			}
			break;

		case 112:
			mciSendString(_T("play sound2"), NULL, 0, NULL);//doorbell sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 116:
			mciSendString(_T("play sound6"), NULL, 0, NULL);//knock sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 117:
			mciSendString(_T("play sound5"), NULL, 0, NULL);//opendoor sfx
			if (m.message == WM_LBUTTONDOWN) {
				currentPage++;
				break;
			}
			break;

		case 122:
			BeginBatchDraw();
			outtextxy(270, 494, L"A. Of course.");
			outtextxy(270, 550, L"B. Sorry, I have to go now.");
			FlushBatchDraw();
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x >= 270 && m.x <= 596 && m.y >= 494 && m.y <= 529) //Option A goes to next page
				{
					currentPage++;
					break;
				}
				else if (m.x >= 270 && m.x <= 754 && m.y >= 550 && m.y <= 585) //Option B goes to chapter 4
				{
					currentPage = 131;
					break;
				}
			}
			break;

		case 123:
			currentPage++;
			mathq();//plays math problem
			break;

		case 139:
			
			if (m.message == WM_LBUTTONDOWN) {
				chapter = 0;//endgame
				savegame();
				exit(0);
			}
			break;
		default:
			if (m.message == WM_LBUTTONDOWN)
			{
				currentPage++;
			}
			break;
		}
		if (m.vkcode == VK_ESCAPE)
			{
			while (flag) {
				pausepage(currentPage);
			}
		}
		EndBatchDraw();
	}
}

//written by felix
//pauses the game
void pausepage(int currentPage) {
	loadimage(&paused, L"../Image/Others/pause.jpg", WIDTH, HEIGHT);
	putimage(0, 0, &paused);
	mciSendString(_T("pause all"), NULL, 0, NULL);
	//written by yuxiao 14/03
	while (flag) {
		getinput();

		BeginBatchDraw();
		putimage(0, 0, &paused);
		settextstyle(40, 0, L"Arial");
		settextcolor(BLACK);
		setbkmode(WHITE);
		outtextxy(385, 395, L"Continue");
		outtextxy(440, 445, L"Quit");
		EndBatchDraw();

		if (m.x >= 440 && m.x <= 520 && m.y >= 445 && m.y <= 480) {
			for (int i = 1; i <= 15; i++)
			{
				BeginBatchDraw();
				setfillcolor(WHITE);
				fillrectangle(400, 430, 540, 500);
				settextstyle(35 + i, 0, L"Arial");
				outtextxy(440 - i, 445 - i, L"Quit");
			}
			FlushBatchDraw();

			//quit button
			//written by felix 14/03
			if (m.message == WM_LBUTTONDOWN) {
				//pops a windows message
				int result = MessageBox(0, L"Do you want to save your game?", L" ", MB_YESNO | MB_SYSTEMMODAL);
				if (result == IDYES) {
					savegame();
					MessageBox(0, L"You saved the game!", L"", 0);
					exit(0);
				}
				else {
					exit(0);
				}

			}
		}
		else if (m.x >= 385 && m.x <= 575 && m.y >= 400 && m.y <= 435) {
			for (int i = 1; i <= 15; i++)
			{
				BeginBatchDraw();
				setfillcolor(WHITE);
				fillrectangle(300, 385, 600, 435);
				settextstyle(35 + i, 0, L"Arial");
				outtextxy(385 - i, 395 - i, L"Continue");
			}
			FlushBatchDraw();
			if (m.message == WM_LBUTTONDOWN)
				return loadgame();
		}
	}
	EndBatchDraw();
}
//written by felix 07/03
//loads the pics
void loadstory0() {
	//chapter 0
	for (int i = 1; i <= 14; i++) {
		_stprintf_s(imagename, _T("../Image/Story/0/P0/0%d.png"), i);//p0 1-14
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
	for (int i = 15; i <= 27; i++) {
		_stprintf_s(imagename, _T("../Image/Story/0/P1/0%d.png"), i);//p1 15-27
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
	for (int i = 28; i <= 35; i++) {
		_stprintf_s(imagename, _T("../Image/Story/0/P2/0%d.png"), i);//p2 28-35
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
	for (int i = 36; i <= 42; i++) {
		_stprintf_s(imagename, _T("../Image/Story/0/P3/0%d.png"), i);//p3 36-42
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
	for (int i = 43; i <= 47; i++) {
		_stprintf_s(imagename, _T("../Image/Story/0/P4/0%d.png"), i);//p4 43-47
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
	for (int i = 48; i <= 53; i++) {
		_stprintf_s(imagename, _T("../Image/Story/0/P5/0%d.png"), i);//p5 48-53
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
	for (int i = 54; i <= 58; i++) {
		_stprintf_s(imagename, _T("../Image/Story/0/P6/0%d.png"), i);//p6 54-58
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
	for (int i = 59; i <= 65; i++) {
		_stprintf_s(imagename, _T("../Image/Story/0/P7/0%d.png"), i);//p7 59-65
		loadimage(&img[i], imagename, WIDTH, HEIGHT);
	}
}

void loadstory1() {
	//chap 1
	for (int i = 0; i <= 29; i++) {
		_stprintf_s(imagename, _T("../Image/Story/1/%d.png"), i);// 66-94
		loadimage(&img[i + 66], imagename, WIDTH, HEIGHT);
	}
}

void loadstory2() {
	//chap 2
	for (int i = 0; i <= 6; i++) {
		_stprintf_s(imagename, _T("../Image/Story/2/%d.png"), i);// 95-101
		loadimage(&img[i + 95], imagename, WIDTH, HEIGHT);
	}
}

void loadstory3() {
	//chap 3
	for (int i = 0; i <= 9; i++) {
		_stprintf_s(imagename, _T("../Image/Story/3/P0/%d.png"), i);//P0 102-111
		loadimage(&img[i + 102], imagename, WIDTH, HEIGHT);
	}
	for (int i = 1; i <= 19; i++) {
		_stprintf_s(imagename, _T("../Image/Story/3/P1/%d.png"), i);//P1 112-130
		loadimage(&img[i + 111], imagename, WIDTH, HEIGHT);
	}
}

void loadstory4() {
	//chap 4
	for (int i = 0; i <= 8; i++) {
		_stprintf_s(imagename, _T("../Image/Story/4/%d.png"), i);//131-139
		loadimage(&img[i + 131], imagename, WIDTH, HEIGHT);
	}
}

//written by felix 07/03
//put the image into the screen
void showpic(int i) {
	putimage(0, 0, &img[i]);
}

//written by felix 07/03
//update 14/03 by felix
//this is the help page
void helppage() {
	loadimage(&help, L"../Image/Others/help.png", WIDTH, HEIGHT);
	putimage(0, 0, &help);
	while (true) {
		getinput();
		switch (m.message) {
		case WM_LBUTTONDOWN:
		case WM_KEYDOWN:
			return startpage();
			break;
		}

	}

}

//written by wangfangxu
//opens the sfx
void opensound() {
	mciSendString(_T("open sound//sound0_page.mp3 alias sound0"), NULL, 0, NULL);
	mciSendString(_T("open sound//sound1_drawer.mp3 alias sound1"), NULL, 0, NULL);
	mciSendString(_T("open sound//sound2_doorbell.mp3 alias sound2"), NULL, 0, NULL);
	mciSendString(_T("open sound//sound3_message.mp3 alias sound3"), NULL, 0, NULL);
	mciSendString(_T("open sound//sound4_unlock.mp3 alias sound4"), NULL, 0, NULL);
	mciSendString(_T("open sound//sound5_opendoor.mp3 alias sound5"), NULL, 0, NULL);
	mciSendString(_T("open sound//sound6_knock.mp3 alias sound6"), NULL, 0, NULL);
}


//written by felix
//puts math image into screen
void showmath(int i) {
	putimage(0, 0, &mathProblem[i]);
}

//written by felix
//math problem
void mathq() {
	//opens the correct bgm
	mciSendString(_T("pause all"), NULL, 0, NULL);
	mciSendString(_T("open bgm//bgm6.mp3 alias mymusic6"), NULL, 0, NULL);
	mciSendString(_T("play mymusic6 repeat"), NULL, 0, NULL);
	initgraph(WIDTH, HEIGHT); 

	//loads image
	for (int i = 1; i <= 3; i++) {
		_stprintf_s(imagename, _T("../Image/Story/3/problem/%d.png"), i);
		loadimage(&mathProblem[i], imagename, WIDTH, HEIGHT);
	}

	static int qnumber = 1;
	while (flag) {
		showmath(qnumber);
		if (qnumber == 1) { //question 1
			InputBox(s, 10, L"Your answer is?",L"Question 1",L"Please type in a number", 300, 0, true);
			int a1 = _wtoi(s);
			int NumberOfTries = 1;
			while (a1 != 18)
			{
				if (NumberOfTries < 3) {
					InputBox(s, 10, L"Wrong ! Try again!", L"Question 1", L"Please type in a number", 300, 0, true);
					a1 = _wtoi(s);
				}
				
				else {
					InputBox(s, 10, L"Wrong ! Try again!\nHint : Chicken have 2 legs and rabbits have 4 legs."
						, L"Question 1", L"Please type in a number", 300, 0, true);
					a1 = _wtoi(s);
				}
				NumberOfTries++;

			}
		}

		if (qnumber == 2) {//question 2
			InputBox(s, 10, L"Your answer is?", L"Question 2", L"Please type in a number", 300, 0, true);
			int a2 = _wtoi(s);
			int NumberOfTries = 1;
			while (a2 != 4)
			{
				if (NumberOfTries < 3) {
					InputBox(s, 10, L"Wrong! Try again!", L"Question 2", L"Please type in a number", 300, 0, true);
					a2 = _wtoi(s);
				}
				else {
					InputBox(s, 10, L"Wrong! Try again!\nHint: Slightly displace one of the cuts to get more pieces.", L"Question 2", L"Please type in a number", 300, 0, true);
					a2 = _wtoi(s);
				}
				NumberOfTries++;
			}
		}
		if (qnumber == 3) {// question 3
			InputBox(s, 10, L"Your answer is?", L"Question 3", L"Please type in a number", 300, 0, true);
			int a3 = _wtoi(s);
			int NumberOfTries = 1;
			while (a3 != 36)
			{
				if (NumberOfTries < 3) {
					InputBox(s, 10, L"Wrong! Try again!", L"Question 3", L"Please type in a number", 300, 0, true);
					a3 = _wtoi(s);
				}
				else {
					InputBox(s, 10, L"Wrong! Try again!\nHint: Count all of the rectangles and squares!", L"Question 3", L"Please type in a number", 300, 0, true);
					a3 = _wtoi(s);
				}
				NumberOfTries++;
			}
			mciSendString(_T("close mymusic6"), NULL, 0, NULL);
			return loadgame();
		}

		qnumber++;
	}
}

//written by yuxiao
// minesweeper part
void minesweeper()
{
	mciSendString(_T("open bgm//bgm5.mp3 alias mymusic5"), NULL, 0, NULL);
	mciSendString(_T("play mymusic5 repeat"), NULL, 0, NULL);
	HWND hwnd = initgraph(grawidth, grahight);
	setbkcolor(RGB(189, 189, 189));
	cleardevice();
	loadimage(&minehelp, _T("../Image/Others/mhelp.png"), WIDTH, HEIGHT);
	//准备过程
	while (ture)
	{
		settextcolor(BLACK);
		settextstyle(40, 0, L"Arial");
		rectangle(80, 50, 250, 120);
		outtextxy(130, 65, L"Play");
		rectangle(80, 150, 250, 220);
		outtextxy(130, 165, L"Help");
		whitchtouth();
	}
	initgraph(WIDTH, HEIGHT);
	putimage(0, 0, &minehelp);
	while (choice) {
		whitchtouth2();
		if (ture == 1) {
			return minesweeper();
		}
	}
	
	cleardevice();
	initgraph(grawidth, grahight);
	setbkcolor(RGB(189, 189, 189));
	cleardevice();
	//开始
	numbombss = bomb % 10;
	numbombs = bomb / 10;
	theloadimage();
	updategame();
	printfmaps();
	while (mineflag)
	{
		printfmap();
		playmine();
		if (win == hight * width - bomb && a)
		{
			a = 0;
			smiles = 3;
			printfmap();
			MessageBox(hwnd, L"You Win!", L"", MB_OK|MB_SYSTEMMODAL);
			minegame++;
			mciSendString(_T("close mymusic5"), NULL, 0, NULL);
			return loadgame();
		}
		if (smiles == 1)//点击笑脸就会重新开始游戏
		{
			first = 1;
			a = 1;
			win = 0;
			system("cls");
			newgame();
			printfmaps();
		}
		end_t = clock();
		int q = (end_t - start_t) / 1000;
		if (runing == 1 && first == 0 && win != hight * width - bomb)
		{
			time1 = q / 100;
			time2 = q / 10 % 10;
			time3 = q % 10;
		}
		if (first == 1)
		{
			time1 = time2 = time3 = 0;
		}

	}
}
void printfmap()
{
	outtextxy(grawidth / 2 - 25, 0, L"Back");
	putimage(grawidth / 2 - 20, 30, &smile[smiles]);//中间笑脸图片
	putimage(10, 10, &numbomb[numbombs]);//这个和下个都是显示炸弹数量图片
	putimage(40, 10, &numbomb[numbombss]);
	putimage(grawidth - 90, 10, &numbomb[time1]);//下面三个都是时间图片
	putimage(grawidth - 60, 10, &numbomb[time2]);
	putimage(grawidth - 30, 10, &numbomb[time3]);
	for (int i = 1; i <= hight; i++)
	{
		for (int j = 1; j <= width; j++)
		{

			int a = (j - 1) * 20;
			int b = (i - 1) * 20 + 72;
			if (map[i][j] <= 28 && map[i][j] >= 19)//19-28表示没点开的所以都是方块图片。这就是为什么要加20的原因
				putimage(a, b, &block[0]);
			else if (map[i][j] <= 8 && map[i][j] >= -1)
			{
				switch (map[i][j])
				{
				case -1:
					putimage(a, b, &block[9]);
					break;
				case 0:
					putimage(a, b, &block[10]);
					break;
				case 1:
					putimage(a, b, &block[1]);
					break;
				case 2:
					putimage(a, b, &block[2]);
					break;
				case 3:
					putimage(a, b, &block[3]);
					break;
				case 4:
					putimage(a, b, &block[4]);
					break;
				case 5:
					putimage(a, b, &block[5]);
					break;
				case 6:
					putimage(a, b, &block[6]);
					break;
				case 7:
					putimage(a, b, &block[7]);
					break;
				case 8:
					putimage(a, b, &block[8]);
					break;
				}
			}//
			//上面这个if就是用来用户点击之后减去20就变成-1到8就显示出对应图片
			else if (map[i][j] <= 48 && map[i][j] >= 39)//右键加20然后，就在39到48之间，这些都是镖旗图标
				putimage(a, b, &block[11]);
			else if (map[i][j] == -100)//这是点到的炸弹要变红
				putimage(a, b, &block[12]);

		}

	}
}
void theloadimage()
{
	//加载图片
	loadimage(&block[0], L"../Image/minesweeper/方块.png", 20, 20 );
	loadimage(&block[1], L"../Image/minesweeper/11.png", 20 , 20 );
	loadimage(&block[2], L"../Image/minesweeper/22.png", 20 , 20 );
	loadimage(&block[3], L"../Image/minesweeper/33.png", 20 , 20 );
	loadimage(&block[4], L"../Image/minesweeper/44.png", 20 , 20 );
	loadimage(&block[5], L"../Image/minesweeper/55.png", 20 , 20 );
	loadimage(&block[6], L"../Image/minesweeper/66.png", 20 , 20 );
	loadimage(&block[7], L"../Image/minesweeper/77.png", 20 , 20 );
	loadimage(&block[8], L"../Image/minesweeper/88.png", 20 , 20 );
	loadimage(&block[9], L"../Image/minesweeper/bom.png", 20 , 20 );
	loadimage(&block[10], L"../Image/minesweeper/方块2.png", 20 , 20 );
	loadimage(&block[11], L"../Image/minesweeper/flag.png", 20 , 20 );
	loadimage(&block[12], L"../Image/minesweeper/red-bom.png", 20 , 20 );
	loadimage(&smile[0], L"../Image/minesweeper/笑脸.png", 30 , 30 );
	loadimage(&smile[1], L"../Image/minesweeper/笑脸2.png", 30 , 30 );
	loadimage(&smile[2], L"../Image/minesweeper/dead.png", 30 , 30 );
	loadimage(&smile[3], L"../Image/minesweeper/cool.png", 30 , 30 );
	for (int i = 0; i <= 9; i++) {
		_stprintf_s(imagename, _T("../Image/minesweeper/%d.png"), i);//number image
		loadimage(&numbomb[i], imagename, 30 , 50 );

	}
}
void playmine()
{
	//获取用户的鼠标输入
	if (MouseHit())//判读有误键盘输入，没有就跳过，免得影响时间的进行，如果没有这个if它会等一下，导致时间是跳动的，读者可以自己删去if来看一下会发生什么
	{
		MOUSEMSG msg = GetMouseMsg();
		int x = msg.x;
		int y = msg.y;
		switch (msg.uMsg)
		{
		case  WM_LBUTTONDOWN:
			if (x >= 0 && x <= grawidth && y >= 72 && y <= grahight && runing && smiles != 3)
			{
				if (first == 1)//判读第一次点击开始计时
				{
					start_t = clock();
					first = 0;
				}
				x = x / 20 + 1;
				y = (y - 72) / 20 + 1;
				if (map[y][x] <= 28 && map[y][x] >= 19)
				{
					if (map[y][x] == 20)//如果点开的是0需要展开周围8个，8个中有0就还要展开，同时保证自己展开的不是炸弹
					{
						openzero(y, x);
					}
					else
					{
						map[y][x] -= 20;//正常的就直接展开
						win++;
						if (map[y][x] == -1)
							win--;//防止最后一个是雷变成又是赢，又有炸弹
					}
				}
				if (map[y][x] == -1)
				{
					map[y][x] = -100;//点到的炸弹要标红，所以单独设置一个数字，来展示这张图片
					showbomb();//点到炸弹要把炸弹全部展开
					smiles = 2;//输了的话就变成哭脸
					printfmap();
					runing = 0;//输了就不能点击游戏区

				}
			}
			else if (x >= grawidth / 2 - 20 && x <= grawidth / 2 + 10 && y >= 20 && y <= 55)
			{
				smiles = 1;
				runing = 1;
			}
			else if (x >= grawidth / 2 - 25 && x <= grawidth / 2 + 10 && y >= 0 && y <= 19)
			{
				before();
				printf("1\n");
			}
			break;
		case WM_LBUTTONUP:
			if (runing == 1 && win != hight * width - bomb)
				smiles = 0;//除了输赢和点击否则都是笑脸
			break;
		case WM_RBUTTONDOWN:
			if (x >= 0 && x <= grawidth && y >= 72 && y <= grahight && runing == 1)//右键镖旗
			{
				if (first == 1)
				{
					start_t = clock();
					first = 0;
				}
				x = x / 20 + 1;
				y = (y - 72) / 20 + 1;
				if (map[y][x] <= 28 && map[y][x] >= 19)
				{
					map[y][x] += 20;

				}
				else if (map[y][x] <= 48 && map[y][x] >= 39)
				{
					map[y][x] -= 20;
				}
			}
			break;


		}

	}

}

//written by yuxiao
//plays the puzzle game
void StartPuzzle()
{
	loadimage(&puzzlehelp, _T("../Image/Others/phelp.png"));
	putimage(0, 0, &puzzlehelp);
	while (flag) {//shows the help page
		getinput();
		if (m.message == WM_LBUTTONDOWN) {
			break;
		}
	}
	initgraph(Len_Image * PicLen, Len_Image * PicLen);
	for (int i = 0; i < PicLen * PicLen; i++)
	{
		_stprintf_s(imagename, _T("../Image/Story/2/puzzle/%d.png"), i);
		loadimage(&puzzleimg[i], imagename, 240, 240);
	}
	CreateMap();
	ShowMap();
	while (puzzleflag)
	{
		Button();
		Mouse();
		judge();
	}
}
void ShowMap()
{
	cleardevice();
	for (int i = 1; i < PicLen + 1; i++)
		for (int j = 1; j < PicLen + 1; j++)
			putimage((i - 1) * Len_Image, (j - 1) * Len_Image, &puzzleimg[Map[i][j]]);
}
void judge()
{
	int Pflag = 1;
	for (int i = 0; i < PicLen * PicLen - 2; i++)
	{
		if (Map[i % PicLen + 1][i / PicLen + 1] >= Map[(i + 1) % PicLen + 1][(i + 1) / PicLen + 1])
		{
			Pflag = 0;
			break;
		}
	}
	if (Pflag)//here is judgement function!!!
	{
		puzzlegame++;
		loadimage(&puzzleans, L"../Image/Story/2/puzzle/answer.png", Len_Image * PicLen, Len_Image * PicLen);
		putimage(0, 0, &puzzleans);
		MessageBox(0, L"You solved the puzzle!", L"", MB_OK| MB_SYSTEMMODAL);
		return loadgame();
	}
}