#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Windows Program 1-2";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	POINT point1[10] = { {460,300}, {510,250},{560,300},{540,350}, {480,350} },
		point2[6] = { {290,250}, {340,350},{240,350} },
		point3[8] = { {350,140}, {450,140},{350,240}, {450,240} },
		point4[10] = { {350,300}, {400,250},{450,300},{430,350}, {370,350} },
		point5[6] = { {400,250}, {450,350},{350,350} },
		point6[8] = { {350,250}, {450,250},{350,350}, {450,350} };
	static int ch;
	static int r[4], g[4], b[4];


	switch (uMsg) {
	case WM_CREATE:
		for (int i = 0; i < 4; ++i)
		{
			r[i] = rand() % 256;
			g[i] = rand() % 256;
			b[i] = rand() % 256;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			ch = 1;
			break;
		case VK_LEFT:
			ch = 2;
			break;
		case VK_UP:
			ch = 3;
			break;
		case VK_DOWN:
			ch = 4;
			break;
		}
		r[ch-1] = rand() % 256;
		g[ch-1] = rand() % 256;
		b[ch-1] = rand() % 256;
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps); 

		Rectangle(hDC, 350, 250, 450, 350);
		//---다각형 그리기---
		hBrush = CreateSolidBrush(RGB(r[0], g[0], b[0]));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Polygon(hDC, point1, 5);	//오각형
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(r[1], g[1], b[1]));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Polygon(hDC, point2, 3);	//삼각형
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(r[2], g[2], b[2]));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Polygon(hDC, point3, 4);	//모레시계
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(r[3], g[3], b[3]));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Pie(hDC, 350, 360, 450, 460, 400, 360, 450, 410);	//파이 모양
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		
		switch (ch)
		{
		case 1:
			hBrush = CreateSolidBrush(RGB(r[0], g[0], b[0]));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Polygon(hDC, point4, 5);	//오각형
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(r[1], g[1], b[1]));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Polygon(hDC, point5, 3);	//삼각형
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(r[2], g[2], b[2]));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Polygon(hDC, point6, 4);	//모레시계
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(r[3], g[3], b[3]));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Pie(hDC, 350, 250, 450, 350, 400, 250, 450, 300);	//파이 모양
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		}
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}