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
	static SIZE size;
	static TCHAR str[1600];	//1600�� ���� �����ϴ� ���ڿ�
	static int count, h, v		//count:���ڸ� ������ ���� �ϳ��� �����ϴ� �ε��� ��-0���� �ڵ� �ʱ�ȭ, k:80�� �̻��Ͻ� �����ٷ� ����, v:������ǥ
		,yPos[10] = {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2}, k;	//����Ű�Է½� ����

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);		//ĳ�� �����	
		ShowCaret(hWnd);					//ĳ�� ǥ��
		break;

	case WM_CHAR:
		if (wParam == VK_RETURN)	//����Ű �Է� ó��
		{
			yPos[k++] = count - 1;	//yPos�� ����Ű�� �Է� �޾��� �� �ε����� ����

			yPos[k] = -1;

			if (k > 9)
				k = 0;
		}
		else str[count++] = wParam;
			str[count] = '\0';

		InvalidateRect(hWnd, NULL, TRUE);	//WM_PAINTȣ��
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		v = 0;	//���� ���� 0���� �ʱ�ȭ
		h = 0; 
		k = 0;

		GetTextExtentPoint32(hDC, L"��", 1, &size);	//���� �ϳ��� �ʺ�� ���� �˾Ƶα�

		for (int i = 0; i < lstrlen(str); ++i)
		{	
			TextOut(hDC, v * size.cx, h * size.cy, &str[i], 1);	//���� ���
			v++;

			while (yPos[k++] == i)
				h++;

			if (v % 5 == 0)	//80�ڰ� �Ǹ� �����ٿ� ���� ���
			{
				v = 0;
				h++;
			}
			if (h % 5 == 0)	//10���� �Ǹ� ó������ ���ư��� �����
			{
				h = 0;
				k = 0;		//k�� 0���� �ʱ�ȭ
			}
		}

		SetCaretPos(v * size.cx, h * size.cy);		//ĳ�� ǥ��

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}