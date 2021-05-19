#pragma once
#include "ChangeAnimationMsg.h"
#include "Message.h"
#include "../../EntityComponentSystem/EntityComponentDef.h"
#include <string>

using namespace std;

class ChangeAnimationMsg : public Message {
public:
	ChangeAnimationMsg(string a_animation, string currentAnim, Entity a_entity);
	string newAnimationState;
	string currentAnimationState;
	Entity entity;
};

