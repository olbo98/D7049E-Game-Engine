#pragma once
#include "Message.h"
#include "../../ControllerSystem/FSM/States/State.h"
#include "../../EntityComponentSystem/EntityComponentDef.h"

class ChangeStateMsg : public Message
{
public:
	ChangeStateMsg(State a_state, Entity a_entity);

	State state;
	Entity entity;
};

