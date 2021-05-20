#pragma once
#include "Message.h"
#include "../../EntityComponentSystem/EntityComponentDef.h"
#include <string>

using namespace std;

class ChangeAnimationMsg : public Message {
public:
	ChangeAnimationMsg();
	string newAnimationState;
	string currentAnimationState;
	Entity entity;
};

