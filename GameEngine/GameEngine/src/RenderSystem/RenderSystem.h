#pragma once
#include "../EntityComponentSystem/System.h"
#include "Renderer.h"

/**
 * A struct containing all the needed elements for
 * a camera
 */
/*struct Camera {
	Ogre::SceneNode* cameraNode;
	Ogre::Camera* camera;
};*/

class RenderSystem : public System {
public:
	void Init();

	void Update(float dt);

	void handleMessage(Message* msg);

private:
	Renderer m_renderer;
};
