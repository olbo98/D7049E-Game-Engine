#pragma once
#include "ComponentArray.h"
#include <unordered_map>
#include <memory>
#include <assert.h>

/**
* CLASS COMPONENT MANAGER 
* The Component Manager is in charge of talking to all of the 
* different ComponentArrays (one for each component type)
* when a component need to be added or removed. 
*/
class ComponentManager
{
public:

	/**
	* Function that add a new component and create its packed array
	*/
	template<typename T>
	void registerComponent()
	{
		// We get the name of the component
		const char* typeName = typeid(T).name();

		assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component type more than once.");

		// Add this component type to the component type map
		m_componentTypes.insert({ typeName, m_nextComponentType });

		// Create a ComponentArray pointer and add it to the component arrays map
		m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		// Increment the value so that the next component registered will be different
		++m_nextComponentType;
	}

	/**
	* Function that returns the id of the actual component
	*/
	template<typename T>
	ComponentType getComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

		// Return this component's type - used for creating signatures
		return m_componentTypes[typeName];
	}

	/**
	* Function that add a component to an entity
	* @param entity The entity to which add the component
	* @param component The component to add
	*/
	template<typename T>
	void addComponent(Entity entity, T component)
	{
		// Add a component to the array for an entity
		getComponentArray<T>()->insertData(entity, component);
	}

	/**
	* Function that remove an entity (and then its linked components)
	* @param entity The entity to delete
	*/
	template<typename T>
	void removeComponent(Entity entity)
	{
		// Remove a component from the array for an entity
		getComponentArray<T>()->removeData(entity);
	}

	/**
	* Function that get a reference to a component from the array for an entity
	* @param entity The entity from which we want the components
	*/
	template<typename T>
	T& getComponent(Entity entity)
	{
		return getComponentArray<T>()->getData(entity);
	}

	/**
	* Function that notify each component array that an entity has been destroyed
	* If it has this entity, it will remove it. 
	* @param entity The entity destroyed
	*/
	void entityDestroyed(Entity entity)
	{
		for (auto const& pair : m_componentArrays)
		{
			auto const& component = pair.second;

			component->entityDestroyed(entity);
		}
	}

private:
	// Map from type string pointer to a component type
	std::unordered_map<const char*, ComponentType> m_componentTypes{};

	// Map from type string pointer to a component array
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays{};

	// The component type to be assigned to the next registered component - starting at 0
	ComponentType m_nextComponentType{};
	
	/**
	* Convenience function to get the statically casted pointer to the ComponentArray of type T
	* @param T The type of component we want the array
	*/
	template<typename T>
	std::shared_ptr<ComponentArray<T>> getComponentArray()
	{
		// Get the name of the component
		const char* typeName = typeid(T).name();

		assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

		// Return a static pointer of the array to the component
		return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
	}
};


