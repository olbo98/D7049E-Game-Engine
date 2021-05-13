#pragma once
#include "../EventSystem/System.h"

class AnimationSystem : public System
{
public:
	AnimationSystem(MessageBus* a_msgBus);
	void handleMessage(Message* msg);
};

