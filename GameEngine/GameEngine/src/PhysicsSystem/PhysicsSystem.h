#pragma once
#include "../EntityComponentSystem/System.h"
#include "Ogre.h"

//! The physics system takes care of applying gracity and velocity to entities with a rigid body
class PhysicsSystem : public System
{
public:
	// Inherited via System
	virtual void handleMessage(Message* msg) override;

	//! Applies gravity to all transforms of rigid body components
	virtual void Update(const Ogre::FrameEvent& fe) override;

private:
	//! The maximum velocity of an entity
	const float MAXIMUM_VELOCITY = 3.0;
};

