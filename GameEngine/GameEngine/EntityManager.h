#pragma once
#include "EntityComponentDef.h"
#include <queue>
#include <array>
#include <assert.h>

/**
* CLASS ENTITY MANAGER 
* 
* The EntityManager class is in charge of
* distributing entity ID’s and keeping record
* of which IDs are in use and which are not.
*/
class EntityManager
{
public:
	EntityManager() {
		// Initialize the queue with all possible entity IDs
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
			m_availableEntities.push(entity);
		}
	}

	/**
	* Function that takes an ID into the queue to create a new entity
	*/
	Entity createEntity() {
		// if we have more living entities than possible --> throw an error
		assert(m_livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		// Take an ID from the front of the queue
		Entity id = m_availableEntities.front();
		m_availableEntities.pop();
		++m_livingEntityCount;

		return id;
	}

	/**
	* Function that destroy an entity an put its ID into the queue
	*/
	void destroyEntity(Entity entity) {
		// if the entity hasn't a valid id --> throw an error
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the destroyed entity's signature
		m_signatures[entity].reset();

		// Put the destroyed ID at the back of the queue
		m_availableEntities.push(entity);
		--m_livingEntityCount;
	}

	/**
	* Function that takes an entity and change its signature
	*/
	void setSignature(Entity entity, Signature signature) {
		// if the entity hasn't a valid id --> throw an error
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		m_signatures[entity] = signature;
	}

	/**
	* Function that returns an entity signature
	*/
	Signature getSignature(Entity entity) {
		// if the entity hasn't a valid id --> throw an error
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return m_signatures[entity];
	}


private:
	// Queue of unused entity IDs
	std::queue<Entity> m_availableEntities;

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> m_signatures;

	// Total living entities - used to keep limits on how many exist
	uint32_t m_livingEntityCount;
};

