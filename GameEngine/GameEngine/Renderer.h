#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"

/**
 * A struct containing all the needed elements for
 * a camera
 */
struct Camera {
	Ogre::SceneNode* cameraNode;
	Ogre::Camera* camera;
};

class Renderer : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	Renderer();
	Renderer(std::string name);
	~Renderer();
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
	* A function that update each entities of the scene
	*/
	void update();

	/**
	* A function that permit to add a new entity in the renderer
	*/
	void addEntity(Ogre::Entity* entity);

	Ogre::Root* m_root;
	Ogre::SceneManager* m_sceneManager;
	Ogre::RTShader::ShaderGenerator* m_shaderGen;
	Ogre::Viewport* m_viewport;

private:
	Camera m_camera;
	std::vector<Ogre::Entity*> m_entities;
};