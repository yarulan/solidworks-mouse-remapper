#include "result.h"

extern State* state;
INPUT inputs[2];

Result drop() {
	return { false, state, 0, 0 };
}

Result drop(State* nextState) {
	return { false, nextState, 0, 0 };
}

Result drop(State* nextState, INPUT input1) {
	inputs[0] = input1;
	return { false, nextState, inputs, 1 };
}

Result drop(State* nextState, INPUT input1, INPUT input2) {
	inputs[0] = input1;
	inputs[1] = input2;
	return { false, nextState, inputs, 2 };
}

Result skip() {
	return { true, state, 0, 0 };
}