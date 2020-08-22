#include "Simulate.h"
#include <dinput.h>

INPUT ip;

void SimulateKeyDown(unsigned int keypress) {
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = keypress;
	SendInput(1, &ip, sizeof(INPUT));
}

void SimulateKeyUp(unsigned int keypress) {
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wScan = keypress;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}