#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

#include "CClsWind.h"
#include "CWind.h"

class CSerialListWind : public CWind {
	CWind *comboBox;
public:
	CSerialListWind(LPCTSTR windowName = TEXT(""), const RECT* dimensions = NULL, DWORD style = CWind::DEF_STYLE, LPCTSTR winClass = 0, WORD menuId = 0) : CWind(windowName, dimensions, style, winClass, menuId), comboBox(nullptr) {
		const RECT comboxBoxDim = {
			10, 10, 120, 110
		};

		comboBox = new CWind(this->GetHandle(), NULL, &comboxBoxDim, WS_CHILD | WS_VISIBLE | CBS_SIMPLE, _T("Combobox"));

		RECT winSize;
		GetClientRect(*this, &winSize);
		SetWindowPos(*comboBox, NULL, 10, 10, winSize.right-20, winSize.bottom-20, 0);
	}

	LRESULT WmSize(HWND hWnd, WPARAM wParam, LPARAM lParam) {
		SetWindowPos(*comboBox, NULL, 10, 10, LOWORD(lParam)-20, HIWORD(lParam)-20, 0);
		return 0;
	}

	void addItem(LPCTSTR portName) {
		SendMessage(*comboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)portName);
	}
};

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	CClsWind winCls(DefWindowProc, CS_HREDRAW | CS_VREDRAW, GetSysColor(COLOR_WINDOW));
	const RECT win123dim = {
		0,0,200,200
	};

	CSerialListWind win1(_T("WinSerialList"), &win123dim, WS_OVERLAPPEDWINDOW | WS_VISIBLE, winCls);

	TCHAR portname[10], path[4096];
	for (size_t i = 0; i < 256; i++) {
		wsprintf(portname, "COM%d", i);
		DWORD res = QueryDosDevice(portname, path, sizeof(path));
		if (res) {
			win1.addItem(portname);
		}
	}
	return CWind::MsgLoop();
}