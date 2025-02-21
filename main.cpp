#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <string>
#include <thread>
#include "hook.h"
#include "input.h"

#define WM_TRAYICON (WM_USER + 1)
#define ID_TRAY_EXIT 1001

HINSTANCE hInst;
NOTIFYICONDATA nid;
HWND hWnd;
HHOOK hMouseHook;
const char* title = "SolidWorks Mouse Remapper";
const char* className = "SolidWorksMouseRemapperClass";

void SetHook() {
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(NULL), 0);
	if (!hMouseHook) {
		MessageBox(NULL, "Failed to install mouse hook!", "Error", MB_ICONERROR);
	}
}

void Unhook() {
	if (hMouseHook) {
		UnhookWindowsHookEx(hMouseHook);
	}
}

void CreateTrayIcon(HWND hWnd) {
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd;
	nid.uID = 1;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_TRAYICON;
	nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	lstrcpy(nid.szTip, TEXT(title));

	Shell_NotifyIcon(NIM_ADD, &nid);
}

void ShowTrayMenu(HWND hWnd) {
	POINT pt;
	GetCursorPos(&pt);
	HMENU hMenu = CreatePopupMenu();

	AppendMenu(hMenu, MF_STRING, ID_TRAY_EXIT, TEXT("Quit"));

	SetForegroundWindow(hWnd);
	TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
	DestroyMenu(hMenu);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_TRAYICON:
		if (LOWORD(lParam) == WM_RBUTTONUP) {
			ShowTrayMenu(hWnd);
		}
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_TRAY_EXIT) {
			Shell_NotifyIcon(NIM_DELETE, &nid);
			PostQuitMessage(0);
		}
		break;

	case WM_DESTROY:
		Shell_NotifyIcon(NIM_DELETE, &nid);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetHook();
	std::thread inputThread(InputWorkerThread);

	hInst = hInstance;
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT(className);

	RegisterClass(&wc);

	hWnd = CreateWindow(TEXT(className), TEXT(title), WS_OVERLAPPEDWINDOW,
		0, 0, 0, 0, NULL, NULL, hInstance, NULL);

	CreateTrayIcon(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	exitThread = true;
	inputThread.join();
	Unhook();

	return 0;
}
