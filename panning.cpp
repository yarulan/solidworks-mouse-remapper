#include "state.h"

Result PanningState::handle(WPARAM wParam) {
	switch (wParam) {
	case WM_MBUTTONUP:
		OutputDebugString("Middle mouse button released, ending panning\n");
		return drop(&waitingState, middleUp, controlUp);
	case WM_MOUSEMOVE:
		return skip();
	default:
		return drop();
	}
}
