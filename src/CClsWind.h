#pragma once

#include <windows.h>
#include <tchar.h>

class CClsWind
{
	ATOM atom;
public:
	CClsWind(void);
	CClsWind(LPCTSTR lpClassName, WNDPROC callback, DWORD dwStyle = CS_HREDRAW | CS_VREDRAW, COLORREF bkgColor = 0xFFFFFF, LPCTSTR cursor = IDC_ARROW);
	CClsWind(WNDPROC callback, DWORD dwStyle = CS_HREDRAW | CS_VREDRAW, COLORREF bkgColor = 0xFFFFFF, LPCTSTR cursor = IDC_ARROW);
	//CClsWind(DWORD dwStyle = CS_HREDRAW | CS_VREDRAW, COLORREF bkgColor = 0xFFFFFF, LPCTSTR cursor = IDC_ARROW);
	~CClsWind(void);

	operator LPCTSTR() const;
	boolean IsValid(void) const;
};
