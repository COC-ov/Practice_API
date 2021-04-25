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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	static SIZE size;
	static TCHAR str[100], str1[100];
	static int count;
	static TCHAR* k = str;
	static int x[3] = { 1, 1, 1 }, i;
	int n=0, m=0;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		break;

	case WM_CHAR:
	
		str[count++] = wParam;
		str[count] = NULL;

		if (wParam == ' ')
		{	
			x[i++] = _wtoi(k);
			k = &(str[count]);
		}

		if (x[0] * x[1] * x[2] == 0)
		{
			HideCaret(hWnd);
			DestroyCaret();
			PostQuitMessage(0);
			//printf("%d %d %d \n", x[0], x[1], x[2]);
		}

		InvalidateRect(hWnd, NULL, TRUE);	//---직접출력하지 않고 WM_PAINT에 메시지 발생
		break;

	case WM_PAINT:		
		hDC = BeginPaint(hWnd, &ps);

		if (i == 3)
		{
			if (x[2] > 19)
			{
				count = 0;
				i = 0;
			}
			else
			{
				for (int i = 1; i < 10; ++i)
				{
					wsprintf(str1, L"%d * %d = %d ", x[2], i, x[2] * i);
					GetTextExtentPoint32(hDC, str1, lstrlen(str1), &size);
					TextOut(hDC, x[0] + (n * size.cx), x[1] + (m * size.cy), str1, lstrlen(str1));//---문자 출력
					n++;
					if ((x[0] + n * size.cx) > 500)
					{
						n = 0;
						m++;
					}
				}

			}

			count = 0;
			i = 0;
			k = str;

			SetCaretPos(0, 0);
		}
		else
		{
			GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
			TextOut(hDC, 0, 0, str, lstrlen(str));//---문자 출력
			SetCaretPos(size.cx, 0);
		}

		EndPaint(hWnd, &ps);
		break;
	
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
