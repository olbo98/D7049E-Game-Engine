#include "RenderSystem.h"
#include "WindowManager.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EntityComponentSystem/Components/MeshRenderable.h"
#include "../EntityComponentSystem/Components/Camera.h"
#include "../EntityComponentSystem/Components/Light.h"

extern Coordinator gCoordinator;
extern WindowManager gWindManager;

void RenderSystem::Init() {
	m_camera = gCoordinator.createEntity();

	Camera cameraComp;
	cameraComp.camera = gWindManager.m_sceneManager->createCamera("MainCamera");
	cameraComp.camera->setNearClipDistance(5);
	gCoordinator.addComponent(
		m_camera, 
		cameraComp);

	Transform cameraTrans;
	cameraTrans.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	cameraTrans.node->setPosition(0, 400, 1000);
	cameraTrans.node->lookAt(Ogre::Vector3(0, 300, 0), Ogre::Node::TransformSpace::TS_WORLD);
	cameraTrans.node->attachObject(cameraComp.camera);
	gCoordinator.addComponent(
		m_camera, 
		cameraTrans);

	// We render it into the main window
	gWindManager.m_viewport = gWindManager.getRenderWindow()->addViewport(cameraComp.camera);
	gWindManager.m_viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	cameraComp.camera->setAspectRatio(Ogre::Real(gWindManager.m_viewport->getActualWidth()) / Ogre::Real(gWindManager.m_viewport->getActualHeight()));

}

void RenderSystem::Update(const Ogre::FrameEvent& fe) {
	// For each entity
	for (auto const& entity : m_entities) {
		auto const& renderable = gCoordinator.getComponent<MeshRenderable>(entity);
		auto const& transform = gCoordinator.getComponent<Transform>(entity);
		// TODO: update the entities
	}
}

void RenderSystem::addSpotLight(Vec3 position, Vec3 direction, std::string name) {
	Entity light = gCoordinator.createEntity();

	Light lightComp;
	lightComp.light = gWindManager.m_sceneManager->createLight(name);
	lightComp.light->setCastShadows(true);    
	lightComp.light->setType(Ogre::Light::LT_SPOTLIGHT);
	lightComp.light->setDiffuseColour(0.3, 0.3, 0.3);
	lightComp.light->setSpecularColour(0.3, 0.3, 0.3);
	gCoordinator.addComponent(light, lightComp);

	Transform trans;
	trans.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans.node->attachObject(lightComp.light);
	trans.node->setPosition(position.x, position.y, position.z);
	trans.node->setDirection(direction.x, direction.y, direction.z);
	gCoordinator.addComponent(light, trans);

}

void RenderSystem::addPointLight(Vec3 position, std::string name) {
	Entity light = gCoordinator.createEntity();

	Light lightComp;
	lightComp.light = gWindManager.m_sceneManager->createLight(name);
	lightComp.light->setCastShadows(true);
	lightComp.light->setType(Ogre::Light::LT_POINT);
	lightComp.light->setDiffuseColour(0.3, 0.3, 0.3);
	lightComp.light->setSpecularColour(0.3, 0.3, 0.3);
	gCoordinator.addComponent(light, lightComp);

	Transform trans;
	trans.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans.node->attachObject(lightComp.light);
	trans.node->setPosition(position.x, position.y, position.z);
	gCoordinator.addComponent(light, trans);
}

void RenderSystem::addDirectionLight(Vec3 position, Vec3 direction, std::string name) {
	Entity light = gCoordinator.createEntity();

	Light lightComp;
	lightComp.light = gWindManager.m_sceneManager->createLight(name);
	lightComp.light->setCastShadows(true);
	lightComp.light->setType(Ogre::Light::LT_DIRECTIONAL);
	lightComp.light->setDiffuseColour(0.3, 0.3, 0.3);
	lightComp.light->setSpecularColour(0.3, 0.3, 0.3);
	gCoordinator.addComponent(light, lightComp);

	Transform trans;
	trans.node = gWindManager.m_sceneManager->getRootSceneNode()->createChildSceneNode();
	trans.node->attachObject(lightComp.light);
	trans.node->setPosition(position.x, position.y, position.z);
	trans.node->setDirection(direction.x, direction.y, direction.z);
	gCoordinator.addComponent(light, trans);
}

void RenderSystem::handleMessage(Message* msg){}