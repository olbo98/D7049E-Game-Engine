#pragma once
#include "Message.h"
#include "../../EntityComponentSystem/EntityComponentDef.h"

class CollisionDetectionMsg : public Message
{
public:
	CollisionDetectionMsg(Entity first, Entity second);
	Entity firstEntity;
	Entity secondEntity;
};

