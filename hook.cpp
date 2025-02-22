#include "hook.h"
#include "state.h"

bool shouldSkip(int nCode, LPARAM lParam) {
	return nCode != 0 || ((MSLLHOOKSTRUCT*)lParam)->flags & LLMHF_INJECTED;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (shouldSkip(nCode, lParam)) {
		goto exit;
	}

	Result result = state->handle(wParam);
	
	for (int i = 0; i < result.numberOfInputs; i++) {
		queueInput(result.inputs[i]);
	}
	
	state = result.nextState;

	if (result.skip) {
		goto exit;
	}

	return 1;

exit:
	return CallNextHookEx(0, nCode, wParam, lParam);
}
