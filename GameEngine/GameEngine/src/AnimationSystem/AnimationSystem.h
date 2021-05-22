#pragma once
#include "../EntityComponentSystem/System.h"
#include "Ogre.h"

//! System that handles all animations that should be rendered
class AnimationSystem : public System
{
public:
	AnimationSystem();
	//! Checks for messages that are of the type CHANGE_ANIMATION and changes the animation state for the specified entity
	virtual void handleMessage(Message* msg) override;
	//! Updates all animations for all entities with an animation component
	virtual void Update(const Ogre::FrameEvent& fe) override;
};

