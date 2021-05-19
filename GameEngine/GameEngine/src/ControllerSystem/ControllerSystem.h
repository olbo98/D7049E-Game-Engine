#pragma once
#include "../EventSystem/System.h"
#include "../InputSystem/InputListener.h"

class ControllerSystem : public InputListener
{
public:
	// Inherited via InputListener
	virtual void onKeyDown(int keyPress, MessageBus* mb) override;
	virtual void onKeyUp(int keyPress, MessageBus* mb) override;

	void update();
};

