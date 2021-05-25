#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "RenderSystem.h"
#include "./../CollisionSystem/CollisionSystem.h"
#include "../AnimationSystem/AnimationSystem.h"
#include "../ControllerSystem/ControllerSystem.h"
#include "../ControllerSystem/Player1Controller.h"
#include "../ControllerSystem/Player2Controller.h"
#include "../InputSystem/InputSystem.h"
#include <iostream>

class WindowManager : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	WindowManager();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool keyReleased(const OgreBites::KeyboardEvent& evt);

	/**
	* A function that initialise the renderer by default
	*/
	void setup();

	/**
	* A function that render the scene
	*/
	void render();

	/**
	* A function called before each frame
	*/
	//virtual bool frameStarted(const Ogre::FrameEvent& evt);

	/**
	* A function called after each frame
	*/
	virtual bool frameEnded(const Ogre::FrameEvent& evt);

	// TODO: add an array of system that go through each system to update, also add an "Update" and "Init" function to 
	// each system
	void addRenderSystem(RenderSystem* renderSystem);
	void addCollisionSystem(CollisionSystem* collisionSystem);
	void addAnimationSystem(AnimationSystem* animSystem);
	void addControllerSystem(ControllerSystem* controllerSystem);
	void addP1Controller(Player1Controller* p1Controller);
	void addP2Controller(Player2Controller* p2Controller);
	void addMessageBus(MessageBus* msgBus);
	void addInputSystem(InputSystem* inputSystem);

	Ogre::Root* m_root;
	Ogre::SceneManager* m_sceneManager;
	Ogre::Viewport* m_viewport;
	RenderSystem* m_renderSystem;
	CollisionSystem* m_collisionSystem;
	AnimationSystem* m_animSystem;
	ControllerSystem* m_controllerSystem;
	Player1Controller* m_p1Controller;
	Player2Controller* m_p2Controller;
	MessageBus* m_msgBus;
	InputSystem* m_inputSystem; 
};
