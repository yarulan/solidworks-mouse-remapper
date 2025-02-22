#include "input.h"

std::queue<INPUT> inputQueue;
std::mutex queueMutex;
bool exitThread = false;

INPUT middleDown = mkMouseInput(MOUSEEVENTF_MIDDLEDOWN);
INPUT rightDown = mkMouseInput(MOUSEEVENTF_RIGHTDOWN);
INPUT rightUp = mkMouseInput(MOUSEEVENTF_RIGHTUP);
INPUT controlDown = mkKeyDown(VK_LCONTROL);
INPUT middleUp = mkMouseInput(MOUSEEVENTF_MIDDLEUP);
INPUT controlUp = mkKeyUp(VK_LCONTROL);

void queueInput(INPUT input) {
	queueInput(&input, 1);
}

void queueInput(INPUT input1, INPUT input2) {
	INPUT inputs[] = { input1, input2 };
	queueInput(inputs, 2);
}

void queueInput(INPUT input[], int size) {
	queueMutex.lock();
	for (int i = 0; i < size; i++) {
		inputQueue.push(input[i]);
	}
	queueMutex.unlock();
}

INPUT mkKeyDown(WORD key, DWORD flags) {
	INPUT input;
	memset(&input, 0, sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	input.ki.dwFlags = flags;
	return input;
}

INPUT mkKeyDown(WORD key) {
	return mkKeyDown(key, 0);
}

INPUT mkKeyUp(WORD key) {
	return mkKeyDown(key, KEYEVENTF_KEYUP);
}

INPUT mkMouseInput(WORD key) {
	INPUT input;
	memset(&input, 0, sizeof(input));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = key;
	return input;
}

void InputWorkerThread() {
	while (!exitThread) {
		if (!inputQueue.empty()) {
			queueMutex.lock();
			INPUT input = inputQueue.front();
			inputQueue.pop();
			queueMutex.unlock();

			SendInput(1, &input, sizeof(INPUT));
		}
		Sleep(1);
	}
}

bool keyUp(int key) {
	return !(GetAsyncKeyState(key) & 0x8000);
}

bool modifierKeysUp() {
	return
		keyUp(VK_SHIFT) &&
		keyUp(VK_CONTROL) &&
		keyUp(VK_MENU) &&
		keyUp(VK_LWIN) &&
		keyUp(VK_RWIN);
}