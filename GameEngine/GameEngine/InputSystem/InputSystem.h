#pragma once
#include "InputListener.h"
#include <map>

/* Publisher class (also a Singleton) that notifies all subscribers/listeners when any state changes */

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void addListeners(InputListener* listener);
	void removeListeners(InputListener* listener);
	void update();

protected:
	//Singleton Object for other classes to fetch
	static InputSystem* inputSystem;
private:

	

	//containers for the listeners
	std::map<InputListener*, InputListener*> map_listeners;

	unsigned char key_states[256] = {};
	unsigned char old_key_states[256] = {};

public:
	static InputSystem* getInstance();
};

