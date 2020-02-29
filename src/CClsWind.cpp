#include <iostream>
#include <cassert>
#include "CClsWind.h"

CClsWind::CClsWind(void) : atom(0) {}

CClsWind::CClsWind(LPCTSTR lpClassName, WNDPROC wndProc, DWORD dwStyle, COLORREF bkgColor, LPCTSTR cursorName) {
	WNDCLASSEX wcex;

	HINSTANCE hInstance = GetModuleHandle(0);

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= dwStyle;
	wcex.lpfnWndProc	= wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(0, cursorName);
	wcex.hbrBackground	= CreateSolidBrush(bkgColor);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= lpClassName;
	wcex.hIconSm		= NULL;

	atom = RegisterClassEx(&wcex);
	assert(atom != 0);
}

CClsWind::CClsWind(WNDPROC wndProc, DWORD dwStyle, COLORREF bkgColor, LPCTSTR cursorName) {
	WNDCLASSEX wcex;
	TCHAR lpClassName[32];

	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	wsprintf(lpClassName, _T("Cls#%08lx"), t.LowPart);

	HINSTANCE hInstance = GetModuleHandle(0);

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= dwStyle;
	wcex.lpfnWndProc	= wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(0, cursorName);
	wcex.hbrBackground	= CreateSolidBrush(bkgColor);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= lpClassName;
	wcex.hIconSm		= NULL;

	atom = RegisterClassEx(&wcex);
	if (atom == 0) {
	DWORD err = GetLastError();
	LPTSTR Error = 0;
	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                    NULL,
                    err,
                    0,
                    (LPTSTR)&Error,
                    0,
                    NULL);
	MessageBox(NULL, Error, _T("GetCurrentDirectory Error"), MB_OK|MB_ICONWARNING );
	}

	assert(atom != 0);
}

CClsWind::~CClsWind(void) {
	if (IsValid()) {
		UnregisterClassA((LPSTR)(DWORD_PTR)atom, GetModuleHandle(0));
	}
}

boolean CClsWind::IsValid(void) const {
	return atom != 0;
}

CClsWind::operator LPCTSTR() const {
	return (LPCTSTR)atom;
}