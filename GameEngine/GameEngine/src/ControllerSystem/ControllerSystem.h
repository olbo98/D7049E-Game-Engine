#pragma once
#include "../EventSystem/System.h"
#include "../InputSystem/InputListener.h"
#include "FSM/PlayerFSM.h"

class ControllerSystem : public InputListener, public System
{
public:
	// Inherited via InputListener
	virtual void onKeyDown(int keyPress) override; //TODO Remove the message bus parameter to the onKeyDown/Up functions
	virtual void onKeyUp(int keyPress) override;

	// Inherited via System
	virtual void handleMessage(Message* msg) override;
private:
	PlayerFSM player1Fsm;
	PlayerFSM player2Fsm;
};

