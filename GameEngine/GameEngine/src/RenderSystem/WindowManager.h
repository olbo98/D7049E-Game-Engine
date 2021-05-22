#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "RenderSystem.h"
#include "./../CollisionSystem/CollisionSystem.h"
#include "../AnimationSystem/AnimationSystem.h"
#include "../ControllerSystem/ControllerSystem.h"
#include <iostream>

class WindowManager : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	WindowManager();
	~WindowManager();
	bool keyPressed(const OgreBites::KeyboardEvent& evt);

	/**
	* A function that initialise the renderer by default
	*/
	void setup();

	/**
	* A function that render the scene
	*/
	void render() const;

	/**
	* A function called before each frame
	*/
	virtual bool frameStarted(const Ogre::FrameEvent& evt);

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
	void addMessageBus(MessageBus* msgBus);

	Ogre::Root* m_root;
	Ogre::SceneManager* m_sceneManager;
	Ogre::RTShader::ShaderGenerator* m_shaderGen;
	Ogre::Viewport* m_viewport;
	RenderSystem* m_renderSystem;
	CollisionSystem* m_collisionSystem;
	AnimationSystem* m_animSystem;
	ControllerSystem* m_controllerSystem;
	MessageBus* m_msgBus;
};