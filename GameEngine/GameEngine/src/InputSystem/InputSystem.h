#pragma once
#include "InputListener.h"
#include "../EntityComponentSystem/System.h"
#include <map>

/* Publisher class (also a Singleton) that notifies all subscribers/listeners when any state changes */

class InputSystem: public System
{

public:
	InputSystem();
	~InputSystem();

	void update();
	void addListeners(InputListener* listener);
	void removeListeners(InputListener* listener);

private:

	//containers for the listeners
	std::map<InputListener*, InputListener*> map_listeners;
	//std::unordered_set<InputListener*> m_set_listeners;

	//states of each key in the keyboard
	unsigned char key_states[256] = {};
	unsigned char old_key_states[256] = {};


public:
	static InputSystem* getInstance();

	// Inherited via System
	virtual void handleMessage(Message* msg) override;
};

