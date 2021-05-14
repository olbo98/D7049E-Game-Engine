#pragma once
#include "Ogre.h"

struct MeshRenderable {
	Ogre::Entity* mesh;
	// TODO: put into transform
	Ogre::SceneNode* renderableNode;
};