#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Windows Program 1-2";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{

	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 0, 0, 800, 800, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	HBRUSH hBrush, oldBrush;
	static int tNum=2;

	switch (uMsg) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 30, NULL);
		break;
	case WM_TIMER:
		if (wParam == 1)
		{
			SetTimer(hWnd, tNum, 30, NULL);
			tNum++;
		}
		break;

	case WM_KEYDOWN:
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps); 
		for (int i = 0; i < 41; ++i)	//줄 41개 그리기
		{
			MoveToEx(hDC, 0 + i * 15, 0, NULL);	//세로
			LineTo(hDC, 0 + i * 15, 600, NULL);
			MoveToEx(hDC, 0, 0 + i * 15, NULL);	//가로
			LineTo(hDC, 600, 0 + i * 15, NULL);

		}

		hBrush = CreateSolidBrush(RGB(255, 204, 102));	//주인공 원 그리기
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, 0, 0, 15, 15);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hDC;
	hDC = GetDC(hWnd);
	HBRUSH hBrush, oldBrush;
	static int x, y;
	switch (idEvent)
	{
	case 2:
		x++;
		y++;
		break;
	}
	hBrush = CreateSolidBrush(RGB(255, 51, 51));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Ellipse(hDC,(20+x)*15, (20+y)*15, (21+x)*15, (21+y)*15);
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, hDC);
}