#include <cstdio>
#include <cassert>
#include "CWind.h"

const RECT CWind::DefRect = {
	0, 0, 640, 480
};

CWind::CWind(LPCTSTR windowName, const RECT* rect, DWORD style, LPCTSTR winClass, WORD menuId) {
	HINSTANCE hInstance = GetModuleHandle(0);

	if (!rect) {
		rect = &DefRect;
	}

	HMENU menu = NULL;
	if (menuId) {
		menu = LoadMenu(hInstance, MAKEINTRESOURCE(menuId));
	}

	m_hWnd = CreateWindowEx(0,
		winClass,
		windowName,
		style,
		rect->left,
		rect->top,
		rect->right,
		rect->bottom,
		NULL,
		menu,
		hInstance,
		NULL);
	assert(m_hWnd);

	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG)(LONG_PTR)this);
	SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG)(LONG_PTR)CWind::WndProc);
}

CWind::CWind(HWND parent, LPCTSTR windowName, const RECT* rect, DWORD style, LPCTSTR winClass) {
	HINSTANCE hInstance = GetModuleHandle(0);

	m_hWnd = CreateWindow(winClass,
		windowName,
		style,
		rect->left,
		rect->top,
		rect->right,
		rect->bottom,
		parent,
		NULL,
		hInstance,
		NULL);
	assert(m_hWnd);
}

CWind::CWind(COLORREF bkgColor, LPCTSTR windowName, const RECT* rect, DWORD style) : LocClsWind(DefWindowProc, CS_HREDRAW | CS_VREDRAW, bkgColor) {
	HINSTANCE hInstance = GetModuleHandle(0);

	m_hWnd = CreateWindowEx(0,
		LocClsWind,
		windowName,
		style,
		rect->left,
		rect->top,
		rect->right,
		rect->bottom,
		NULL,
		NULL,
		hInstance,
		NULL);
	assert(m_hWnd);

	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG)(LONG_PTR)this);
	SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG)(LONG_PTR)CWind::WndProc);
}

CWind::~CWind(void) {
	DestroyWindow(m_hWnd);
}


HWND CWind::GetHandle(void) const {
	return m_hWnd;
}

CWind::operator HWND(void) const {
	return m_hWnd;
}

void CWind::SetStyle(LONG s) {
    SetWindowLongPtr(m_hWnd,GWL_STYLE,(LONG)(LONG_PTR)s);
    SetWindowPos(m_hWnd,0,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

void CWind::SetExStyle(LONG s) {
	SetWindowLongPtr(m_hWnd,GWL_EXSTYLE,(LONG)(LONG_PTR)s);
    SetWindowPos(m_hWnd,0,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

LRESULT CALLBACK CWind::evtHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int res = -1;

#ifdef USE_CONSOLE
	printf("WndProc: msg=%94lx\n", message);
#endif // USE_CONSOLE

	switch (message) {
	case WM_CREATE: res = WmCreate(hWnd, wParam, lParam); break;
	case WM_COMMAND: res = WmCommand(hWnd, wParam, lParam); break;
	case WM_PAINT: res = WmPaint(hWnd, wParam, lParam); break;
	case WM_TIMER: res = WmTimer(hWnd, wParam, lParam); break;
	case WM_CLOSE: res = WmClose(hWnd, wParam, lParam); break;
	case WM_MOUSEHOVER: res = WmMouseHover(hWnd, wParam, lParam); break;
	case WM_MOUSEMOVE: res = WmMouseMove(hWnd, wParam, lParam); break;
	case WM_LBUTTONDOWN: res = WmLButtonDown(hWnd, wParam, lParam); break;
	case WM_RBUTTONDOWN: res = WmRButtonDown(hWnd, wParam, lParam); break;
	case WM_MOUSELEAVE: res = WmMouseLeave(hWnd, wParam, lParam); break;
	case WM_KEYDOWN: res = WmKeyDown(hWnd, wParam, lParam); break;
	case WM_SIZE: res = WmSize(hWnd, wParam, lParam); break;
	case WM_DESTROY: PostQuitMessage(0); break;
	default: break;
	}

	if (res == 0) {
		return 0;
	} else {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

int CWind::MsgLoop(void) {
	MSG msg;
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK CWind::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	CWind* windPtr = (CWind*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	return windPtr->evtHandler(hWnd, message, wParam, lParam);
}

LRESULT CWind::WmPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmTimer(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmCreate(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmKeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmMButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmMButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmRButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmDropFiles(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmMouseHover(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmMouseLeave(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}

LRESULT CWind::WmSize(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return -1;
}
