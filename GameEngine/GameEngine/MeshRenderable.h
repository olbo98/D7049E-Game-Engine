#pragma once
#include "Ogre.h"

struct MeshRenderable {
	Ogre::Entity* mesh;
	Ogre::SceneNode* renderableNode;
};
