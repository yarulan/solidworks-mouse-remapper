#pragma once

#include <windows.h>

extern HHOOK hMouseHook;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);