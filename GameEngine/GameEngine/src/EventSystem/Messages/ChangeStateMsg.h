#pragma once
#include "Message.h"
#include "../../ControllerSystem/FSM/States/State.h"

class ChangeStateMsg : public Message
{
public:
	ChangeStateMsg(State a_state);

	State state;
};

