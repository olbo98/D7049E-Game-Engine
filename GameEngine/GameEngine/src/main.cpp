#include "EntityComponentSystem/Coordinator.h"
#include "EntityComponentSystem/Components/Camera.h"
#include "EntityComponentSystem/Components/MeshRenderable.h"
#include "EntityComponentSystem/Components/Transform.h"
#include "EntityComponentSystem/Components/Light.h"
#include "EntityComponentSystem/Components/BoxCollider.h"
#include "EntityComponentSystem/Components/Animation.h"
#include "EntityComponentSystem/Components/PlayerId.h"
#include "EntityComponentSystem/Components/SceneComponent.h"
#include "EntityComponentSystem/EntityComponentDef.h"
#include "RenderSystem/RenderSystem.h"
#include "RenderSystem/WindowManager.h"
#include "CollisionSystem/CollisionSystem.h"
#include "InputSystem/InputSystem.h"
#include <iostream>

#include "EventSystem/MessageBus.h"
#include "ControllerSystem/ControllerSystem.h"
#include "ControllerSystem/Player1Controller.h"
#include "ControllerSystem//Player2Controller.h"
#include "AnimationSystem/AnimationSystem.h"
#include "InputSystem/InputSystem.h"

MessageBus msgBus;
Coordinator gCoordinator;
WindowManager gWindManager;

int main(int argc, char* argv[])
{
	InputSystem* iSys = InputSystem::getInstance();
	AnimationSystem* aSys = new AnimationSystem();
	msgBus.addReciever(aSys);
	gWindManager.initApp();
	gCoordinator.init();

	 //Register Components
	gCoordinator.registerComponent<Camera>();
	gCoordinator.registerComponent<MeshRenderable>();
	gCoordinator.registerComponent<Transform>();
	gCoordinator.registerComponent<Light>();
	gCoordinator.registerComponent<BoxCollider>();
	gCoordinator.registerComponent<Animation>();
	gCoordinator.registerComponent<PlayerId>();
	gCoordinator.registerComponent<SceneComponent>();

	gWindManager.addInputSystem(iSys);

	 //Register render system
	auto renderSystem = gCoordinator.registerSystem<RenderSystem>();
	{
		 //Each entity used in the renderSystem must have a Mesh renderable component and a Transform component
		Signature signature;
		signature.set(gCoordinator.getComponentType<MeshRenderable>());
		signature.set(gCoordinator.getComponentType<Transform>());
		gCoordinator.setSystemSignature<RenderSystem>(signature);
	}
	renderSystem->Init();
	 //Try to add a light to check
	renderSystem->addPointLight(Vec3(0, 150, 250));
	renderSystem->addDirectionLight(Vec3(300, 0, 0), Vec3(-1, 0, 0));
	gWindManager.addRenderSystem(renderSystem.get());

	 //Register physic system
	auto collideSystem = gCoordinator.registerSystem<CollisionSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.getComponentType<Transform>());
		signature.set(gCoordinator.getComponentType<BoxCollider>());
		gCoordinator.setSystemSignature<CollisionSystem>(signature);
	}
	collideSystem->Init();
	gWindManager.addCollisionSystem(collideSystem.get());

	 //Register animation system
	auto animSystem = gCoordinator.registerSystem<AnimationSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.getComponentType<Animation>());
		gCoordinator.setSystemSignature<AnimationSystem>(signature);
	}
	animSystem->Init();
	gWindManager.addAnimationSystem(animSystem.get());

	 //Register controller system
	//auto controllerSystem = gCoordinator.registerSystem<ControllerSystem>();
	auto p1Controller = gCoordinator.registerSystem<Player1Controller>();
	{
		Signature signature;
		signature.set(gCoordinator.getComponentType<PlayerId>());
		gCoordinator.setSystemSignature<Player1Controller>(signature);
	}
	p1Controller->Init();
	//iSys->addListeners(controllerSystem.get());
	gWindManager.addP1Controller(p1Controller.get());
	msgBus.addReciever(p1Controller.get());

	auto p2Controller = gCoordinator.registerSystem<Player2Controller>();
	{
		Signature signature;
		signature.set(gCoordinator.getComponentType<PlayerId>());
		gCoordinator.setSystemSignature<Player2Controller>(signature);
	}
	p2Controller->Init();
	//iSys->addListeners(controllerSystem.get());
	gWindManager.addP2Controller(p2Controller.get());
	msgBus.addReciever(p2Controller.get());

	gWindManager.addMessageBus(&msgBus);

	 //Create an entity to render
	
	Entity entity = gCoordinator.createEntity();
	p1Controller->setActiveEntity(entity);

	MeshRenderable meshRend;
	meshRend.mesh = gWindManager.m_sceneManager->createEntity("Abe.mesh");
	meshRend.mesh->setCastShadows(true);
	gCoordinator.addComponent(entity, meshRend);

	Transform trans;
	trans.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans.node->setPosition(150, 0, 0);
	trans.node->attachObject(meshRend.mesh);
	trans.node->yaw(Ogre::Radian(-3.14/2));
	gCoordinator.addComponent(entity, trans);

	BoxCollider collider;
	collider.relativePosition = Vec3(0, 0, 0);
	collider.boxSize = Vec3(100, 100, 100);
	gCoordinator.addComponent(entity, collider);

	PlayerId player1Id;
	player1Id.playerId = 1;
	gCoordinator.addComponent(entity, player1Id);

	
	
	//Enable all aimations for entity
	Ogre::AnimationState* idleState = meshRend.mesh->getAnimationState("Idle");
	idleState->setEnabled(true);
	idleState->setLoop(true);
	Ogre::AnimationState* jmpState = meshRend.mesh->getAnimationState("Jumping");
	jmpState->setLoop(false);
	Ogre::AnimationState* lPunchState = meshRend.mesh->getAnimationState("Light_punch");
	lPunchState->setLoop(false);
	Ogre::AnimationState* hPunchState = meshRend.mesh->getAnimationState("Heavy_punch");
	hPunchState->setLoop(false);
	Ogre::AnimationState* lKickState = meshRend.mesh->getAnimationState("Light_kick");
	lKickState->setLoop(false);
	Ogre::AnimationState* hKickState = meshRend.mesh->getAnimationState("Heavy_kick");
	hKickState->setLoop(false);

	//Create animation component
	Animation animComp;
	animComp.animation = idleState;
	gCoordinator.addComponent(entity, animComp);

	Entity entity2 = gCoordinator.createEntity();
	p2Controller->setActiveEntity(entity2);

	MeshRenderable meshRend2;
	meshRend2.mesh = gWindManager.m_sceneManager->createEntity("Abe.mesh");
	meshRend2.mesh->setCastShadows(true);
	gCoordinator.addComponent(entity2, meshRend2);

	Transform trans2;
	trans2.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans2.node->setPosition(150, 10, 0);
	trans2.node->yaw(Ogre::Radian(3.14/2));
	trans2.node->attachObject(meshRend2.mesh);
	gCoordinator.addComponent(entity2, trans2);

	BoxCollider collider2;
	collider2.relativePosition = Vec3(0, 0, 0);
	collider2.boxSize = Vec3(100, 100, 100);
	gCoordinator.addComponent(entity2, collider2);

	PlayerId player2Id;
	player2Id.playerId = 2;
	gCoordinator.addComponent(entity2, player2Id);

	//Enable all aimations for entity
	Ogre::AnimationState* idleState2 = meshRend2.mesh->getAnimationState("Idle");
	idleState2->setEnabled(true);
	idleState2->setLoop(true);
	Ogre::AnimationState* jmpState2 = meshRend2.mesh->getAnimationState("Jumping");
	jmpState2->setLoop(false);
	Ogre::AnimationState* lPunchState2 = meshRend2.mesh->getAnimationState("Light_punch");
	lPunchState2->setLoop(false);
	Ogre::AnimationState* hPunchState2 = meshRend2.mesh->getAnimationState("Heavy_punch");
	hPunchState2->setLoop(false);
	Ogre::AnimationState* lKickState2 = meshRend2.mesh->getAnimationState("Light_kick");
	lKickState2->setLoop(false);
	Ogre::AnimationState* hKickState2 = meshRend2.mesh->getAnimationState("Heavy_kick");
	hKickState2->setLoop(false);

	//Create animation component
	Animation animComp2;
	animComp2.animation = idleState2;
	gCoordinator.addComponent(entity2, animComp2);
	
	Entity scene = gCoordinator.createEntity();

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground", Ogre::RGN_DEFAULT,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	MeshRenderable meshRendS;
	meshRendS.mesh = gWindManager.m_sceneManager->createEntity("ground");
	meshRendS.mesh->setCastShadows(true);
	meshRendS.mesh->setMaterialName("Examples/Rockwall");
	gCoordinator.addComponent(scene, meshRendS);

	Transform transS;
	transS.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	transS.node->setPosition(0, 0, 0);
	transS.node->attachObject(meshRendS.mesh);
	gCoordinator.addComponent(scene, transS);

	BoxCollider colliderS;
	colliderS.relativePosition = Vec3(0, 0, 0);
	colliderS.boxSize = Vec3(100, 100, 100);
	gCoordinator.addComponent(scene, colliderS);

	SceneComponent sceneComp;
	gCoordinator.addComponent(scene, sceneComp);

	gWindManager.render();

	gWindManager.closeApp();
	return 0;
}
