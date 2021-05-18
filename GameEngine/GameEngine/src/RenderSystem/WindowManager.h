#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "RenderSystem.h"
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

	void addRenderSystem(RenderSystem* renderSystem);

	Ogre::Root* m_root;
	Ogre::SceneManager* m_sceneManager;
	Ogre::RTShader::ShaderGenerator* m_shaderGen;
	Ogre::Viewport* m_viewport;
	RenderSystem* m_renderSystem;
};