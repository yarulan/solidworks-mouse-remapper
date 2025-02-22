#pragma once

#include <windows.h>
#include "hook.h"
#include "input.h"
#include "result.h"

class State {
public:
	virtual Result handle(WPARAM wParam) = 0;
};

class WaitingState : public State {
	Result handle(WPARAM wParam);
};

class PanningState : public State {
	Result handle(WPARAM wParam);
};

class RotationWaitingState : public State {
	Result handle(WPARAM wParam);
};

class RotatingState : public State {
	Result handle(WPARAM wParam);
};

extern WaitingState waitingState;
extern PanningState panningState;
extern RotationWaitingState rotationWaitingState;
extern RotatingState rotatingState;

extern State* state;

bool solidWorksWindowActive();