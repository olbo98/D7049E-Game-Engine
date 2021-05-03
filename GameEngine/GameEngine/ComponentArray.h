#pragma once
#include "EntityComponentDef.h"

// An interface is needed so that the ComponentManager
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.
class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void entityDestroyed(Entity entity) = 0;
};


/**
* CLASS COMPONENTARRAY
* The ComponentArray class is a packed array (no holes inside) of components.
* It contains a mapping from entity IDs to array indices and from array indices
* to entity IDs. So as to keep track of the relations between each entity and their
* components.
*/
template<typename T>
class ComponentArray : public IComponentArray
{
public:
	/**
	* A function that insert a new component into the array and links it to an entity
	* @param entity The entity to which we add a component
	* @param component The component we add
	*/
	void insertData(Entity entity, T component)
	{
		assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end and update the maps
		size_t newIndex = m_size;
		m_entityToIndexMap[entity] = newIndex;
		m_indexToEntityMap[newIndex] = entity;
		m_componentArray[newIndex] = component;
		++m_size;
	}

	/**
	* A function that remove an entity (an then its stored components)
	* @param entity The entity we remove
	*/
	void removeData(Entity entity)
	{
		assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = m_size - 1;
		m_componentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		m_entityToIndexMap.erase(entity);
		m_indexToEntityMap.erase(indexOfLastElement);

		--m_size;
	}

	/**
	* A function that return a reference to the entity's component
	* @param entity The entity we want to get the component
	*/
	T& getData(Entity entity)
	{
		assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Retrieving non-existent component.");

		// Return a reference to the entity's component
		return m_componentArray[m_entityToIndexMap[entity]];
	}


	/**
	* A function that destroy the given entity
	*/
	void entityDestroyed(Entity entity) override
	{
		if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
		{
			// Remove the entity's component if it existed
			removeData(entity);
		}
	}

private:
	// The packed array of components (that can be any type thanks to the generic type T),
	// set to a specified maximum amount, matching the maximum number
	// of entities allowed to exist simultaneously, so that each entity
	// has a unique spot.
	std::array<T, MAX_ENTITIES> m_componentArray;

	// Map from an entity ID to an array index.
	std::unordered_map<Entity, size_t> m_entityToIndexMap;

	// Map from an array index to an entity ID.
	std::unordered_map<size_t, Entity> m_indexToEntityMap;

	// Total size of valid entries in the array.
	size_t m_size;
};


