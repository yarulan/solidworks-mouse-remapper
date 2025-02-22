#include "state.h"
#include "result.h"

Result WaitingState::handle(WPARAM wParam) {
	if (wParam == WM_MBUTTONDOWN) {
		OutputDebugString("Middle mouse button pressed\n");
		if (modifierKeysUp() && solidWorksWindowActive()) {
			return drop(&panningState, controlDown, middleDown);
		} else {
			return skip();
		}
	} else if (wParam == WM_RBUTTONDOWN) {
		OutputDebugString("Right mouse button pressed\n");
		if (modifierKeysUp() && solidWorksWindowActive()) {
			return drop(&rotationWaitingState);
		} else {
			return skip();
		}
	} else {
		return skip();
	}
}