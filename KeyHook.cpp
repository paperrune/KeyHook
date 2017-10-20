#include "KeyHook.h"

KeyHook KeyHook::keyHook;

LRESULT WINAPI keyProc(int nCode, WPARAM wParam, LPARAM lParam){
	return KeyHook::keyHook.keyProc(nCode, wParam, lParam);
}

KeyHook::KeyHook(){
	hook = SetWindowsHookExA(WH_KEYBOARD_LL, ::keyProc, GetModuleHandle(NULL), 0);
}

KeyHook::~KeyHook(){
	if (hook) UnhookWindowsHookEx(hook);
}

void KeyHook::Disable(){
	delegate = nullptr;
}

LRESULT WINAPI KeyHook::keyProc(int nCode, WPARAM wParam, LPARAM lParam){
	if (delegate->onKey((KBDLLHOOKSTRUCT *)lParam)) return true;

	return CallNextHookEx(hook, nCode, wParam, lParam);
}
