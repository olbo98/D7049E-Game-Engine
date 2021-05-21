#pragma once
#include "ComponentArray.h"
#include "../EntityComponentSystem/System.h"
#include <unordered_map>
#include <memory>

/**
* CLASS SYSTEM MANAGER
* The System Managaer class is in charge of maintaining a record 
* of registered systems and their signature. This is the same way of working than the Component Manager.
*/
class SystemManager
{
public:

	/**
	* Function that add a new system and create a pointer that we return to use it externally
	*/
	template<typename T>
	std::shared_ptr<T> registerSystem()
	{
		const char* typeName = typeid(T).name();

		assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

		auto system = std::make_shared<T>();
		m_systems.insert({ typeName, system });
		return system;
	}

	/**
	* Function that change the signature for the current system
	* @param signature The signature to set
	*/
	template<typename T>
	void setSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

		// Set the signature for this system
		m_signatures.insert({ typeName, signature });
	}

	/**
	* Function that erase a destroyed entity from all system lists
	* @param entity The entity to destroy
	*/
	void entityDestroyed(Entity entity)
	{
		for (auto const& pair : m_systems)
		{
			auto const& system = pair.second;

			system->m_entities.erase(entity);
		}
	}

	/**
	* Function that notify each system that an entity's signature changed
	* @param entity The entity to change the signature to
	* @param entitySignature The signature to apply to the entity
	*/
	void entitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : m_systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = m_signatures[type];

			// Entity signature matches system signature - insert into set
			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->m_entities.insert(entity);
			}
			// Entity signature does not match system signature - erase from set
			else
			{
				system->m_entities.erase(entity);
			}
		}
	}

private:
	// Map from system type string pointer to a signature
	std::unordered_map<const char*, Signature> m_signatures{};

	// Map from system type string pointer to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
};
