#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX, 0, 0, 900, 700, NULL, (HMENU)NULL, hInstance, NULL);
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
	PAINTSTRUCT ps;
	HDC hDC;

	switch (uMsg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		SetBkColor(hDC, RGB(100, 200, 50));
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, 0, 0, L"Left-Top(0, 0)", strlen("Left-Top(0, 0)"));
		SetBkColor(hDC, RGB(200, 0, 100));
		SetTextColor(hDC, RGB(0, 0, 255));
		TextOut(hDC, 700, 0, L"Right-Top(700, 0)", strlen("Right-Top(700, 0)"));
		SetBkColor(hDC, RGB(200, 200, 200));
		SetTextColor(hDC, RGB(180, 0, 0));
		TextOut(hDC, 350, 300, L"Center(700, 0)", strlen("Center(700, 0)"));
		SetBkColor(hDC, RGB(100, 250, 100));
		SetTextColor(hDC, RGB(255, 255, 255));
		TextOut(hDC, 0, 650, L"Left-bottom(0, 650)", strlen("Left-bottom(0, 650)"));
		SetBkColor(hDC, RGB(255, 255, 100));
		SetTextColor(hDC, RGB(255, 100,100));
		TextOut(hDC, 700, 650, L"Right-bottom(700, 650)", strlen("Right-bottom(700, 650)"));

		EndPaint(hWnd, &ps);	
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); // 위의 세 메시지 외의 나머지 메시지는 OS로
}
