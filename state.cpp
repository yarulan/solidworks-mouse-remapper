#include "state.h"

bool solidWorksWindowActive();
bool modifierKeysUp();

WaitingState waitingState;
PanningState panningState;
RotationWaitingState rotationWaitingState;
RotatingState rotatingState;

State* state = &waitingState;

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