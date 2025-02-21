#pragma once

#include <windows.h>
#include "hook.h"

class State;

struct HandleResult {
	bool shouldSkip;
	State* nextState;
};

class State {
public:
	virtual bool handles(WPARAM wParam) = 0;
	virtual State* handle(WPARAM wParam) = 0;
};

class WaitingState : public State {
	bool handles(WPARAM wParam);
	State* handle(WPARAM wParam);
};

class PanningState : public State {
	bool handles(WPARAM wParam);
	State* handle(WPARAM wParam);
};

class RotationWaitingState : public State {
	bool handles(WPARAM wParam);
	State* handle(WPARAM wParam);
};

class RotatingState : public State {
	bool handles(WPARAM wParam);
	State* handle(WPARAM wParam);
};

extern WaitingState waitingState;
extern PanningState panningState;
extern RotationWaitingState rotationWaitingState;
extern RotatingState rotatingState;

extern State* state;