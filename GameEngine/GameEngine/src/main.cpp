#include "EntityComponentSystem/Coordinator.h"
#include "EntityComponentSystem/Components/Camera.h"
#include "EntityComponentSystem/Components/MeshRenderable.h"
#include "EntityComponentSystem/Components/Transform.h"
#include "EntityComponentSystem/Components/Light.h"
#include "EntityComponentSystem/EntityComponentDef.h"
#include "RenderSystem/RenderSystem.h"
#include "RenderSystem/WindowManager.h"
/*#include "../src/AudioSystem/SoundDevice.h"
#include "../src/AudioSystem/SoundBuffer.h"
#include "../src/AudioSystem/SoundSource.h"
#include "../src/AudioSystem/MusicBuffer.h"*/
#include <iostream>


WindowManager gWindManager;
Coordinator gCoordinator;

int main(int argc, char* argv[])
{
	gWindManager.initApp();
	gCoordinator.init();

	// Register Components
	gCoordinator.registerComponent<Camera>();
	gCoordinator.registerComponent<MeshRenderable>();
	gCoordinator.registerComponent<Transform>();
	gCoordinator.registerComponent<Light>();

	// Register render system
	auto renderSystem = gCoordinator.registerSystem<RenderSystem>();
	{
		// Each entity used in the renderSystem must have a Mesh renderable component and a Transform component
		Signature signature;
		signature.set(gCoordinator.getComponentType<MeshRenderable>());
		signature.set(gCoordinator.getComponentType<Transform>());
		gCoordinator.setSystemSignature<RenderSystem>(signature);
	}
	renderSystem->Init();
	// Try to add a light to check
	renderSystem->addPointLight(Vec3(0, 150, 250));
	renderSystem->addDirectionLight(Vec3(300, 0, 0), Vec3(-1, 0, 0));
	gWindManager.addRenderSystem(renderSystem.get());

	// Create an entity to render
	Entity entity = gCoordinator.createEntity();

	MeshRenderable meshRend;
	meshRend.mesh = gWindManager.m_sceneManager->createEntity("ninja.mesh");
	meshRend.mesh->setCastShadows(true);
	gCoordinator.addComponent(entity, meshRend);

	Transform trans;
	trans.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans.node->setPosition(150, 0, 0);
	trans.node->attachObject(meshRend.mesh);
	gCoordinator.addComponent(entity, trans);


	Entity entity2 = gCoordinator.createEntity();

	MeshRenderable meshRend2;
	meshRend2.mesh = gWindManager.m_sceneManager->createEntity("ninja.mesh");
	meshRend2.mesh->setCastShadows(true);
	gCoordinator.addComponent(entity2, meshRend2);

	Transform trans2;
	trans2.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans2.node->setPosition(0, 0, 0);
	trans2.node->setOrientation(1, 0, 0.65, 0);
	trans2.node->attachObject(meshRend2.mesh);
	gCoordinator.addComponent(entity2, trans2);

	gWindManager.render();

	gWindManager.closeApp();
	return 0;
}
