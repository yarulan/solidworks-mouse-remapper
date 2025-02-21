#include "state.h"
#include "input.h"

bool solidWorksWindowActive();
bool modifierKeysUp();

WaitingState waitingState;
PanningState panningState;
RotationWaitingState rotationWaitingState;
RotatingState rotatingState;

State* state = &waitingState;

bool WaitingState::handles(WPARAM wParam) {
	bool middleButtonDown = wParam == WM_MBUTTONDOWN;
	bool rightButtonDown = wParam == WM_RBUTTONDOWN;
	bool middleOrRightButtonDown = middleButtonDown || rightButtonDown;
	return middleOrRightButtonDown && modifierKeysUp() && solidWorksWindowActive();
}

State* WaitingState::handle(WPARAM wParam) {
	if (wParam == WM_MBUTTONDOWN) {
		OutputDebugString("Middle mouse button pressed\n");
		INPUT controlDown = mkKeyDown(VK_LCONTROL);
		INPUT middleDown = mkMouseInput(MOUSEEVENTF_MIDDLEDOWN);
		queueInput(controlDown, middleDown);
		return &panningState;
	} else if (wParam == WM_RBUTTONDOWN) {
		OutputDebugString("Right mouse button pressed\n");
		return &rotationWaitingState;
	} else {
		OutputDebugString("Unreachable");
		exit(1);
	}
}

bool PanningState::handles(WPARAM wParam) {
	return wParam == WM_MBUTTONUP;
}

State* PanningState::handle(WPARAM wParam) {
	OutputDebugString("Middle mouse button released\n");
	INPUT middleUp = mkMouseInput(MOUSEEVENTF_MIDDLEUP);
	INPUT controlUp = mkKeyUp(VK_LCONTROL);
	queueInput(middleUp, controlUp);
	return &waitingState;
}

bool RotationWaitingState::handles(WPARAM wParam) {
	return true;
}

State* RotationWaitingState::handle(WPARAM wParam) {
	if (wParam == WM_MOUSEMOVE) {
		OutputDebugString("Mouse moved\n");
		INPUT middleDown = mkMouseInput(MOUSEEVENTF_MIDDLEDOWN);
		queueInput(middleDown);
		return &rotatingState;
	} else if (wParam == WM_RBUTTONUP) {
		OutputDebugString("Right mouse button released without move\n");
		INPUT rightDown = mkMouseInput(MOUSEEVENTF_RIGHTDOWN);
		INPUT rightUp = mkMouseInput(MOUSEEVENTF_RIGHTUP);
		queueInput(rightDown, rightUp);
		return &waitingState;
	} else {
		return this;
	}
}

bool RotatingState::handles(WPARAM wParam) {
	return wParam == WM_RBUTTONUP;
}
State* RotatingState::handle(WPARAM wParam) {
	OutputDebugString("Right mouse button released\n");
	INPUT middleUp = mkMouseInput(MOUSEEVENTF_MIDDLEUP);
	queueInput(middleUp);
	return &waitingState;
}

bool solidWorksWindowActive() {
	HWND handle = GetForegroundWindow();

	if (!handle) {
		return false;
	}

	char title[256];

	int length = GetWindowText(handle, title, sizeof(title));

	if (length <= 0) {
		return false;
	}

	return strstr(title, "SOLIDWORKS") != NULL;
}