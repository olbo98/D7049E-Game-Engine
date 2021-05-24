#include "CollisionSystem.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EntityComponentSystem/Components/BoxCollider.h"
#include "../EntityComponentSystem/Components/SceneComponent.h"
#include "../EntityComponentSystem/Components/PlayerId.h"
#include "../EventSystem/Messages/CollisionDetectionMsg.h"
#include "../EventSystem/MessageBus.h"
#include <iostream>


extern Coordinator gCoordinator;
extern MessageBus msgBus;

void CollisionSystem::Init() {

}

void CollisionSystem::Update() {
	// For each entity
	for (auto const& entity : m_entities) {
		auto const& collider = gCoordinator.getComponent<BoxCollider>(entity);
		auto const& transform = gCoordinator.getComponent<Transform>(entity);
		for (auto const& collideEntity : m_entities) {
			if (entity != collideEntity) {
				auto const& secondCollider = gCoordinator.getComponent<BoxCollider>(collideEntity);
				auto const& secondTransform = gCoordinator.getComponent<Transform>(collideEntity);
				Vec3 pos1 = getColliderPos(transform.node->getPosition(), collider.relativePosition);
				Vec3 pos2 = getColliderPos(secondTransform.node->getPosition(), secondCollider.relativePosition);
				if (doCollide(pos1, pos2, collider.boxSize, secondCollider.boxSize)) {
					CollisionDetectionMsg* collisionMsg = new CollisionDetectionMsg(entity, collideEntity);
					msgBus.postMessage(collisionMsg);
				}

			}
		}
		
	}
}

Vec3 CollisionSystem::getColliderPos(Vec3 transPos, Vec3 relativePos) {
	return transPos + relativePos;
}

bool CollisionSystem::doCollide(Vec3 pos1, Vec3 pos2, Vec3 size1, Vec3 size2) {
	int AxMin(pos1.x), AxMax(pos1.x + size1.x),
		AyMin(pos1.y), AyMax(pos1.y + size1.y),
		AzMin(pos1.z), AzMax(pos1.z + size1.z),
		BxMin(pos2.x), BxMax(pos2.x + size2.x),
		ByMin(pos2.y), ByMax(pos2.y + size2.y),
		BzMin(pos2.z), BzMax(pos2.z + size2.z);
	return (AxMin < BxMax && AxMax > BxMin) 
		&& (AyMin < ByMax && AyMax > ByMin) 
		&& (AzMin < BzMax && AzMax > BzMin);

}

void CollisionSystem::handleMessage(Message* msg) {}