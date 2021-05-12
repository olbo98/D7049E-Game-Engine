#pragma once

/* Interface class to inherit */
class InputListener {

public:
	InputListener() {

	}
	~InputListener() {

	}

	//virtual functions for keyboard
	virtual void onKeyDown(int keyPress) = 0;
	virtual void onKeyUp(int keyPress) = 0;
};