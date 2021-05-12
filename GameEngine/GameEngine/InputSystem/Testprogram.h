#pragma once
#include"InputListener.h"
class Testprogram: public InputListener
{
	// Inherited via InputListener
	virtual void onKeyDown(int keyPress) override;
	virtual void onKeyUp(int keyPress) override;
};

