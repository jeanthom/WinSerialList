#pragma once

#include <windows.h>
#include <tchar.h>
#include "CClsWind.h"

class CWind
{
protected:
	HWND m_hWnd;
	CClsWind LocClsWind;

	virtual LRESULT CALLBACK evtHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmKeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmMButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmMButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmRButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmDropFiles(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmMouseHover(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmMouseLeave(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WmSize(HWND hWnd, WPARAM wParam, LPARAM lParam);

public:
	static const DWORD DEF_STYLE = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	static const RECT DefRect;

	CWind(LPCTSTR windowName = TEXT(""), const RECT* dimensions = NULL, DWORD style = DEF_STYLE, LPCTSTR winClass = 0, WORD menuId = 0);
	CWind(COLORREF bkgColor, LPCTSTR windowName, const RECT* rect, DWORD style);
	CWind(HWND parent, LPCTSTR windowName = _T(""), const RECT* dimensions = NULL, DWORD style = DEF_STYLE, LPCTSTR winClass = 0);
	~CWind(void);

	HWND GetHandle() const;
	operator HWND() const;
	void SetStyle(LONG s);
	void SetExStyle(LONG s);

	static int MsgLoop(void);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
