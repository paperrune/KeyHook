#include "KeyHook.h"

class Delegate : public KeyHookDelegate{
	bool onKey(const KBDLLHOOKSTRUCT *p){
		printf("vkCode: %d	scanCode: %d	", p->vkCode, p->scanCode);

		if ((p->flags & 128) == 0){
			printf("down\n");
		}
		else{
			printf("up\n");
		}

		if (p->vkCode == 65 /*A*/){
			printf("key blocked\n");
			return true;
		}
		return false;
	}
};

int main(){
	MSG msg;

	KeyHook::keyHook.Enable<Delegate>();

	// KeyHook::KeyHook.Disable();

	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
