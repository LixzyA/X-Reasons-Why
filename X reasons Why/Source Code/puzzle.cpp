#include "puzzle.h"


//written by yuxiao and wangfangxu
extern int Map[MapLen][MapLen];
int  key;
int  dx[4] = { -1, 1, 0, 0 };
int  dy[4] = { 0, 0, -1, 1 };
int Zero_pos[2] = { PicLen, PicLen };
int res = -1;
int nowmove;

LRESULT CALLBACK CBTHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND)wParam;
	if (nCode == HCBT_ACTIVATE)
	{
		if (nCode == HCBT_ACTIVATE)
		{
			SetDlgItemText((HWND)wParam, IDYES, L"&3×3");
			SetDlgItemText((HWND)wParam, IDNO, L"&4×4");
			SetDlgItemText((HWND)wParam, IDOK, L"&OK");
			SetDlgItemText((HWND)wParam, IDCANCEL, L"&无屏障(困难)");
			SetDlgItemText((HWND)wParam, IDABORT, L"&有屏障");
			SetDlgItemText((HWND)wParam, IDRETRY, L"&无屏障");
			SetDlgItemText((HWND)wParam, IDIGNORE, L"&BGM已关闭");
		}
	}
	return 0;
}
int Msg(HWND hwnd, TCHAR* szText, TCHAR* szCaption, UINT uType)
{
	int ret;
	HHOOK hHook = SetWindowsHookEx(WH_CBT, CBTHookProc, NULL, GetCurrentThreadId());
	ret = MessageBox(hwnd, szText, szCaption, uType);
	UnhookWindowsHookEx(hHook);
	return ret;
}
int Dir(int x, int y)
{
	if ((abs(Zero_pos[0] - x) + abs(Zero_pos[1] - y)) == 1)
	{
		if (Zero_pos[0] - x == -1)
			return 0;
		if (Zero_pos[0] - x == 1)
			return 1;
		if (Zero_pos[1] - y == -1)
			return 2;
		if (Zero_pos[1] - y == 1)
			return 3;
	}
	return -1;
}
void CreateMap()
{

	for (int i = 0; i < MapLen; i++)
		for (int j = 0; j < MapLen; j++)
			if (i == 0 || i == (MapLen - 1) || j == 0 || j == (MapLen - 1))
				Map[i][j] = Blank_Map;

	for (int i = 0; i < PicLen * PicLen; i++)
		Map[i % PicLen + 1][i / PicLen + 1] = i + 1;

	Map[PicLen][PicLen] = 0;

	srand((unsigned int)time(NULL));
	int tt;
	for (int i = 0; i < 200; i++)
	{
		tt = rand() % 4 + 1;
		switch (tt)
		{
		case 1:
			nowmove = 1;
			break;
		case 2:
			nowmove = 0;
			break;
		case 3:
			nowmove = 3;
			break;
		case 4:
			nowmove = 2;
			break;
		}
		if ((Zero_pos[0] + dx[nowmove]) >= 1
			&& (Zero_pos[0] + dx[nowmove]) <= PicLen
			&& (Zero_pos[1] + dy[nowmove]) >= 1
			&& (Zero_pos[1] + dy[nowmove]) <= PicLen
			)
		{
			Map[Zero_pos[0]][Zero_pos[1]] = Map[Zero_pos[0] + dx[nowmove]][Zero_pos[1] + dy[nowmove]];
			Zero_pos[0] = Zero_pos[0] + dx[nowmove];
			Zero_pos[1] = Zero_pos[1] + dy[nowmove];
			Map[Zero_pos[0]][Zero_pos[1]] = 0;
		}
	}
}

int LOCAL_XY(double pos)
{
	return (int)(pos / 245 + 1);
}

void Button()
{
	if (_kbhit() != 0)
	{
		while (_kbhit() != 0)
			key = _getch();

		switch (key)
		{
		case 75:
			nowmove = 1;
			break;
		case 77:
			nowmove = 0;
			break;
		case 72:
			nowmove = 3;
			break;
		case 80:
			nowmove = 2;
			break;
		}
		if ((Zero_pos[0] + dx[nowmove]) >= 1
			&& (Zero_pos[0] + dx[nowmove]) <= PicLen
			&& (Zero_pos[1] + dy[nowmove]) >= 1
			&& (Zero_pos[1] + dy[nowmove]) <= PicLen
			)
		{
			Map[Zero_pos[0]][Zero_pos[1]] = Map[Zero_pos[0] + dx[nowmove]][Zero_pos[1] + dy[nowmove]];//交换值 并记录空白格位置
			Zero_pos[0] = Zero_pos[0] + dx[nowmove];
			Zero_pos[1] = Zero_pos[1] + dy[nowmove];
			Map[Zero_pos[0]][Zero_pos[1]] = 0;
			ShowMap();
		}
	}
}
void Mouse()//鼠标移动
{
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			int nowmove = Dir(LOCAL_XY(msg.x), LOCAL_XY(msg.y));
			if (nowmove != -1)
			{

				Map[LOCAL_XY(msg.x) + dx[nowmove]][LOCAL_XY(msg.y) + dy[nowmove]] = Map[LOCAL_XY(msg.x)][LOCAL_XY(msg.y)];
				Map[LOCAL_XY(msg.x)][LOCAL_XY(msg.y)] = 0;
				Zero_pos[0] = LOCAL_XY(msg.x);
				Zero_pos[1] = LOCAL_XY(msg.y);
				ShowMap();
			}
			break;
		}
	}
}