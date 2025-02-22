#pragma once

#include <windows.h>

class State;

struct Result {
	bool skip;
	State* nextState;
	INPUT* inputs;
	int numberOfInputs;
};

Result drop();
Result drop(State* nextState);
Result drop(State* nextState, INPUT input1);
Result drop(State* nextState, INPUT input1, INPUT input2);
Result skip();