#include "EntityComponentSystem/Coordinator.h"
#include "EntityComponentSystem/Components/Camera.h"
#include "EntityComponentSystem/Components/MeshRenderable.h"
#include "EntityComponentSystem/Components/Transform.h"
#include "EntityComponentSystem/Components/Light.h"
#include "EntityComponentSystem/Components/BoxCollider.h"
#include "EntityComponentSystem/Components/RigidBody.h"
#include "EntityComponentSystem/EntityComponentDef.h"
#include "PhysicsSystem/PhysicsSystem.h"
#include "RenderSystem/RenderSystem.h"
#include "RenderSystem/WindowManager.h"
#include "CollisionSystem/CollisionSystem.h"
////#include "../src/audiosystem/sounddevice.h"
////#include "../src/audiosystem/soundbuffer.h"
////#include "../src/audiosystem/soundsource.h"
////#include "../src/audiosystem/musicbuffer.h"
#include <iostream>

#include "EventSystem/MessageBus.h"
#include "ControllerSystem/ControllerSystem.h"
#include "EntityComponentSystem/Coordinator.h"
#include "AnimationSystem/AnimationSystem.h"
#include "InputSystem/InputSystem.h"

MessageBus msgBus;
Coordinator gCoordinator;
WindowManager gWindManager;

int main(int argc, char* argv[])
{
	InputSystem* iSys = InputSystem::getInstance();
	ControllerSystem* cSys = new ControllerSystem();
	AnimationSystem* aSys = new AnimationSystem();
	msgBus.addReciever(cSys);
	msgBus.addReciever(aSys);
	gWindManager.initApp();
	gCoordinator.init();

	// Register Components
	gCoordinator.registerComponent<Camera>();
	gCoordinator.registerComponent<MeshRenderable>();
	gCoordinator.registerComponent<Transform>();
	gCoordinator.registerComponent<Light>();
	gCoordinator.registerComponent<BoxCollider>();
	gCoordinator.registerComponent<RigidBody>();

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
	renderSystem->addPointLight(Vec3(0, 150, -250), "PointLight1");
	renderSystem->addPointLight(Vec3(0, 150, 250), "PointLight2");
	renderSystem->addDirectionLight(Vec3(300, 0, 0), Vec3(-1, 0, 0));
	gWindManager.addSystem(renderSystem.get());

	// Register physic system
	auto collideSystem = gCoordinator.registerSystem<CollisionSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.getComponentType<Transform>());
		signature.set(gCoordinator.getComponentType<BoxCollider>());
		gCoordinator.setSystemSignature<CollisionSystem>(signature);
	}
	gWindManager.addSystem(collideSystem.get());

	auto physicSystem = gCoordinator.registerSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.getComponentType<Transform>());
		signature.set(gCoordinator.getComponentType<RigidBody>());
		gCoordinator.setSystemSignature<PhysicsSystem>(signature);
	}
	gWindManager.addSystem(physicSystem.get());

	// TRY TO APPLY GRAVITY TO A HUNDRED ENTITIES
	for (int i = 0; i < 100; i++) {
		Entity entity = gCoordinator.createEntity();

		MeshRenderable meshRend;
		meshRend.mesh = gWindManager.m_sceneManager->createEntity("ninja.mesh");
		meshRend.mesh->setCastShadows(true);
		gCoordinator.addComponent(entity, meshRend);

		Transform trans;
		trans.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
		trans.node->setPosition(i*40, 0, 0);
		trans.node->attachObject(meshRend.mesh);
		gCoordinator.addComponent(entity, trans);

		BoxCollider collider;
		collider.relativePosition = Vec3(0, 0, 0);
		collider.boxSize = Vec3(100, 100, 100);
		gCoordinator.addComponent(entity, collider);

		RigidBody rigidbody;
		rigidbody.gravity = i*0.005;
		rigidbody.upwardsVelocity = 0;
		gCoordinator.addComponent(entity, rigidbody);

	}

	// Create an entity to render
	/*Entity entity = gCoordinator.createEntity();

	MeshRenderable meshRend;
	meshRend.mesh = gWindManager.m_sceneManager->createEntity("ninja.mesh");
	meshRend.mesh->setCastShadows(true);
	gCoordinator.addComponent(entity, meshRend);

	Transform trans;
	trans.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans.node->setPosition(150, 0, 0);
	trans.node->attachObject(meshRend.mesh);
	gCoordinator.addComponent(entity, trans);

	BoxCollider collider;
	collider.relativePosition = Vec3(0, 0, 0);
	collider.boxSize = Vec3(100, 100, 100);
	gCoordinator.addComponent(entity, collider);

	Entity entity2 = gCoordinator.createEntity();

	MeshRenderable meshRend2;
	meshRend2.mesh = gWindManager.m_sceneManager->createEntity("ninja.mesh");
	meshRend2.mesh->setCastShadows(true);
	gCoordinator.addComponent(entity2, meshRend2);

	Transform trans2;
	trans2.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans2.node->setPosition(0, 0, 0);
	trans2.node->attachObject(meshRend2.mesh);
	gCoordinator.addComponent(entity2, trans2);

	BoxCollider collider2;
	collider2.relativePosition = Vec3(0, 0, 0);
	collider2.boxSize = Vec3(100, 100, 100);
	gCoordinator.addComponent(entity2, collider2);

	RigidBody rigidbody;
	rigidbody.gravity = 0.9;
	rigidbody.upwardsVelocity = 1;
	gCoordinator.addComponent(entity2, rigidbody);*/

	gWindManager.render();

	gWindManager.closeApp();
	return 0;
}
