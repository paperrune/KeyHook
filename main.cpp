#include "KeyHook.h"

class Delegate : public KeyHookDelegate{
	void onKey(const KBDLLHOOKSTRUCT *p){
		printf("vkCode: %d	scanCode: %d	", p->vkCode, p->scanCode);

		if ((p->flags & 128) == 0){
			printf("down\n");
		}
		else{
			printf("up\n");
		}
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