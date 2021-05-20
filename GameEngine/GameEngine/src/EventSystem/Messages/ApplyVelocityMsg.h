#pragma once
#include "Message.h"
#include "../../EntityComponentSystem/EntityComponentDef.h"

class ApplyVelocityMsg : public Message
{
public:
	ApplyVelocityMsg();

	//! Entity to apply velocity to
	Entity entity;
};

