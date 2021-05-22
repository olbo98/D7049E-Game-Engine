#include "PhysicsSystem.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../EntityComponentSystem/Components/RigidBody.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EventSystem/Messages/ApplyVelocityMsg.h"
#include "../Utils/Utils.h"


extern Coordinator gCoordinator;

void PhysicsSystem::handleMessage(Message* msg)
{
	MessageId messageTypeToCheck = MessageId::APPLY_VELOCITY;
	if (msg->checkId(&messageTypeToCheck)) {
		ApplyVelocityMsg* message = (ApplyVelocityMsg*)msg;
		Entity ent = message->entity;
		auto& rigidBodyComponent = gCoordinator.getComponent<RigidBody>(ent);
		rigidBodyComponent.upwardsVelocity = MAXIMUM_VELOCITY;
	}
}

void PhysicsSystem::Update(const Ogre::FrameEvent& fe) {
	for (auto const& entity : m_entities) {
		auto& rigidBodyComponent = gCoordinator.getComponent<RigidBody>(entity);
		auto& transformComponent = gCoordinator.getComponent<Transform>(entity);

		float currentYVelocity = rigidBodyComponent.upwardsVelocity;
		Vec3 currentPosition = transformComponent.node->getPosition();
		float gravity = rigidBodyComponent.gravity;

		Vec3 distToMove = Vec3(0, 1, 0) * currentYVelocity;
		
		Vec3 newPos = currentPosition + distToMove;
		transformComponent.node->setPosition(newPos.toOgre());

		float newVelocity = currentYVelocity - gravity;
		if (newVelocity > MAXIMUM_VELOCITY) {
			newVelocity = MAXIMUM_VELOCITY;
		}
		else if (newVelocity < MAXIMUM_VELOCITY * -1) {
			newVelocity = MAXIMUM_VELOCITY * -1;
		}

		rigidBodyComponent.upwardsVelocity = newVelocity;
	}
}
