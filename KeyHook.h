#include <memory>
#include <Windows.h>

class KeyHookDelegate : public std::enable_shared_from_this<KeyHookDelegate>{
	friend class KeyHook;

public:
	std::shared_ptr<KeyHookDelegate> shared(){
		return shared_from_this();
	}
protected:
	virtual bool onKey(const KBDLLHOOKSTRUCT *) = 0;
};

class KeyHook{
	friend LRESULT WINAPI keyProc(int nCode, WPARAM wParam, LPARAM lParam);

private:
	HHOOK hook;

	std::shared_ptr<KeyHookDelegate> delegate;

	LRESULT WINAPI keyProc(int nCode, WPARAM wParam, LPARAM lParam);
public:
	static KeyHook keyHook;

	KeyHook();
	~KeyHook();

	void Disable();

	template<typename T>
	void Enable(){
		std::shared_ptr<T> ptr(new T);

		delegate = ptr;
	}
};
