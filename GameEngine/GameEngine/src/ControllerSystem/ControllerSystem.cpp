#include "ControllerSystem.h"

void ControllerSystem::onKeyDown(int keyPress, MessageBus* mb)
{
	switch (keyPress)
	{
	case 87://W
		//create message and send to animation to start jumping anim
		//Move transform up?
	case 83://S
		//create message and send to animation to start crouch anim
	case 65://A
		//create message and send to animation to start walking back anim
		//move transform to the left
	case 68://D
		//create message and send to animation to start walking forward anim
		//move transform to the right
	case 32://Space
		//Create message and send to animation to start jumping animation
		//Move transform up?
	default:
		break;
	}
}

void ControllerSystem::onKeyUp(int keyPress, MessageBus* mb)
{
}
