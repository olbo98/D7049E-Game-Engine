#pragma once
#include "../EventSystem/System.h"
#include "Ogre.h"

class PhysicsSystem : public System
{
public:
	// Inherited via System
	virtual void handleMessage(Message* msg) override;

	void update(const Ogre::FrameEvent& fe);

private:
	const float MAXIMUM_VELOCITY = 3.0;
};

