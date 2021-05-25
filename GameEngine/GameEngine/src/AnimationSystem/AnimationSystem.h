#pragma once
#include "../EntityComponentSystem/System.h"
#include "Ogre.h"
#include <string>
#include <iostream>
#include "../EntityComponentSystem/Components/Animation.h"
#include "../EntityComponentSystem/Components/MeshRenderable.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EventSystem/Messages/ChangeAnimationMsg.h"
#include "../EventSystem/Messages/ChangeStateMsg.h"

//! System that handles all animations that should be rendered
class AnimationSystem : public System
{
public:
	void Init();
	//! Checks for messages that are of the type CHANGE_ANIMATION and changes the animation state for the specified entity
	virtual void handleMessage(Message* msg) override;
	//! Updates all animations for all entities with an animation component

	void Update(const Ogre::FrameEvent& fe);

	void changeAnim(Entity entity, string newAnim);
};

