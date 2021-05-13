#pragma once
#include "../EventSystem/MessageBus.h"

/* Interface class to inherit */
class InputListener {

public:
	InputListener() {

	}
	~InputListener() {

	}

	//virtual functions for keyboard
	virtual void onKeyDown(int keyPress, MessageBus* mb) = 0;
	virtual void onKeyUp(int keyPress, MessageBus* mb) = 0;
};