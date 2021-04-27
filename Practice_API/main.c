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
	static SIZE size;
	static TCHAR str[1600];	//1600자 까지 저장하는 문자열
	static int count, h, v		//count:문자를 받을때 마다 하나씩 증가하는 인덱스 값-0으로 자동 초기화, k:80자 이상일시 다음줄로 변경, v:가로좌표
		,yPos[10] = {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2}, k;	//엔터키입력시 증가

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);		//캐럿 만들기	
		ShowCaret(hWnd);					//캐럿 표시
		break;

	case WM_CHAR:
		if (wParam == VK_RETURN)	//엔터키 입력 처리
		{
			yPos[k++] = count - 1;	//yPos에 엔터키를 입력 받았을 때 인덱스를 저장

			yPos[k] = -1;

			if (k > 9)
				k = 0;
		}
		else str[count++] = wParam;
			str[count] = '\0';

		InvalidateRect(hWnd, NULL, TRUE);	//WM_PAINT호출
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		v = 0;	//가로 세로 0으로 초기화
		h = 0; 
		k = 0;

		GetTextExtentPoint32(hDC, L"윈", 1, &size);	//문자 하나의 너비와 높이 알아두기

		for (int i = 0; i < lstrlen(str); ++i)
		{	
			TextOut(hDC, v * size.cx, h * size.cy, &str[i], 1);	//문자 출력
			v++;

			while (yPos[k++] == i)
				h++;

			if (v % 5 == 0)	//80자가 되면 다음줄에 문자 출력
			{
				v = 0;
				h++;
			}
			if (h % 5 == 0)	//10줄이 되면 처음으로 돌아가서 덮어쓰기
			{
				h = 0;
				k = 0;		//k도 0으로 초기화
			}
		}

		SetCaretPos(v * size.cx, h * size.cy);		//캐럿 표시

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}