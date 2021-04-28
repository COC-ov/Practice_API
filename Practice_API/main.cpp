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
	static RECT rectView;
	static bool flag;
	static int x, y;

	switch (uMsg) {
	case WM_CREATE:
		GetClientRect(hWnd, &rectView);
		x = 20; y = 20;
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		if (flag)
			SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
		Ellipse(hDC, x - 20, y - 20, x + 20, y + 20);
		EndPaint(hWnd, &ps);
		break;

	case WM_KEYUP:
		flag = false;
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
		{
			flag = true;
			x += 40;
			if (x + 20 > rectView.right) x -= 40;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
