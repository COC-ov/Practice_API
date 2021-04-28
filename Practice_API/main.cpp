#include <windows.h> //--- ������ ��� ����
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
	HBRUSH hBrush, oldBrush;
	static int tNum = 2, x, y, count2, k = 1;

	switch (uMsg) {
	case WM_CREATE:
		//SetTimer(hWnd, 1, 300, NULL);
		break;

	case WM_CHAR:
		switch (wParam)
		{
		case 's':
		case 'S':
			SetTimer(hWnd, 2, 50, NULL);
			break;
		}
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case 2:
			if (count2 % 2 == 0)	//������׷� �̵�
				x += k;
			if (count2 % 2 == 1)
				y += k;

			if (x > 39 || x < 0)
			{
				k *= (-1);
				x += k;
			}

			if (y > 39 || y < 0)
			{
				k *= (-1);
				y += k;
			}
			count2++;	//0.3�ʸ��� count2 1�� ����
			break;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_KEYDOWN:
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 41; ++i)	//�� 41�� �׸���
		{
			MoveToEx(hDC, 0 + i * 15, 0, NULL);	//����
			LineTo(hDC, 0 + i * 15, 600);
			MoveToEx(hDC, 0, 0 + i * 15, NULL);	//����
			LineTo(hDC, 600, 0 + i * 15);

		}

		hBrush = CreateSolidBrush(RGB(255, 204, 102));	//���ΰ� �� �׸���
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, 0 + (x * 15), 0 + (y * 15), 15 + (x * 15), 15 + (y * 15));
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);


		//---���� �� �׸���---

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		break;
	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}