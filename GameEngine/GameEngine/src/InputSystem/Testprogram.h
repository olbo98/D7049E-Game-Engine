#pragma once
#include"InputListener.h"
class Testprogram: public InputListener
{
public:
	Testprogram();
	
	// Inherited via InputListener
	virtual void onKeyDown(int keyPress, MessageBus* mb) override;
	virtual void onKeyUp(int keyPress, MessageBus* mb) override;
};

