#include "Renderer.h"

Renderer::Renderer() : OgreBites::ApplicationContext("Renderer") {
	OgreBites::ApplicationContext::setup();
	init();
}

Renderer::Renderer(std::string name) : OgreBites::ApplicationContext(name) {
	OgreBites::ApplicationContext::setup();
	init();
}


void Renderer::init() {
	m_root = getRoot();
	m_sceneManager = m_root->createSceneManager();

	m_shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	m_shaderGen->addSceneManager(m_sceneManager);

	m_sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	m_camera.cameraNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	m_camera.camera = m_sceneManager->createCamera("MainCam");
	m_camera.cameraNode->setPosition(200, 300, 400);
	m_camera.cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);
	m_camera.camera->setNearClipDistance(5);
	m_camera.cameraNode->attachObject(m_camera.camera);

	m_viewport = getRenderWindow()->addViewport(m_camera.camera);

	m_viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	m_camera.camera->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) / Ogre::Real(m_viewport->getActualHeight()));

}

void Renderer::render() const {

}

void Renderer::update() {

}