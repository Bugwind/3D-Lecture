
#pragma once


namespace framework
{

	// ������ ����
	HWND InitWindow(HINSTANCE hInstance, 
		const string &windowName, 
		const RECT &windowRect,
		int nCmdShow,
		WNDPROC WndProc);

}
