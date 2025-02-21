#pragma once

#include <windows.h>
#include <mutex>
#include <queue>

extern std::queue<INPUT> inputQueue;
extern std::mutex queueMutex;
extern bool exitThread;

void InputWorkerThread();
void queueInput(INPUT input);
void queueInput(INPUT input1, INPUT input2);
void queueInput(INPUT input[], int size);
INPUT mkKeyDown(WORD key, DWORD flags);
INPUT mkKeyDown(WORD key);
INPUT mkKeyUp(WORD key);
INPUT mkMouseInput(WORD key);
bool modifierKeysUp();