#include "hook.h"
#include "state.h"

bool shouldSkip(int nCode, LPARAM lParam) {
	return nCode != 0 || ((MSLLHOOKSTRUCT*)lParam)->flags & LLMHF_INJECTED;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (shouldSkip(nCode, lParam)) {
		goto exit;
	}


	if (!state->handles(wParam)) {
		goto exit;
	}
	
	State* nextState = state->handle(wParam);
	state = nextState;

	return 1;

exit:
	return CallNextHookEx(0, nCode, wParam, lParam);
}
