#include "RenderSystem.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EntityComponentSystem/Components/MeshRenderable.h"


// Moving entities --> use scene node, update positions
// Handle adding Ogre Entities into the scene

Coordinator gCoordinator;

void RenderSystem::Init() {
	m_renderer.initApp();
	m_renderer.setup();
}

void RenderSystem::Update(float dt) {
	m_renderer.render();
	// For each entity
	for (auto const& entity : m_entities) {
		auto const& renderable = gCoordinator.getComponent<MeshRenderable>(entity);
		renderable.renderableNode->attachObject(renderable.mesh);
		m_renderer.addEntity(renderable.mesh);
	}

	m_renderer.update();
}

void handleMessage(Message* msg){}