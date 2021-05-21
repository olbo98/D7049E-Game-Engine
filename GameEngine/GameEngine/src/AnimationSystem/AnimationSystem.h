#pragma once
#include "../EntityComponentSystem/System.h"
#include "Ogre.h"

//! System that handles all animations that should be rendered
class AnimationSystem : public System
{
public:
	AnimationSystem();
	//! Checks for messages that are of the type CHANGE_ANIMATION and changes the animation state for the specified entity
	void handleMessage(Message* msg);
	//! Updates all animations for all entities with an animation component
	void update(const Ogre::FrameEvent& fe);
};

