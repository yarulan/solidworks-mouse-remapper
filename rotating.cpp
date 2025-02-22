#include "state.h"

Result RotationWaitingState::handle(WPARAM wParam) {
	if (wParam == WM_MOUSEMOVE) {
		OutputDebugString("Mouse moved, starting rotation\n");
		return drop(&rotatingState, middleDown);
	} else if (wParam == WM_RBUTTONUP) {
		OutputDebugString("Right mouse button released without move, pressing right mouse button\n");
		return drop(&waitingState, rightDown, rightUp);
	} else {
		return drop(&waitingState);
	}
}

Result RotatingState::handle(WPARAM wParam) {
	if (wParam == WM_MOUSEMOVE) {
		return skip();
	} else if (wParam == WM_RBUTTONUP) {
		OutputDebugString("Right mouse button released, ending rotation\n");
		return drop(&waitingState, middleUp);
	} else {
		return drop(&waitingState);
	}
}