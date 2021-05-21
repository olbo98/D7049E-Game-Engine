#pragma once
#include <bitset>
#include <cstdint>

	/**
	* ENTITY
	* An entity is just an ID that will be used as an index
	* to an array of components.
	*/
	// ID of the entity
	using Entity = std::uint32_t;

	// Number max of entities available
	const Entity MAX_ENTITIES = 5000;

	/**
	* COMPONENT
	* A component is a struct with a small chunk of functionality
	* related data. Each component type has a unique ID given to it (see below).
	*/
	// ID of the component
	using ComponentType = std::uint8_t;

	const ComponentType MAX_COMPONENTS = 32;

	/**
	* SIGNATURE
	* Each component type has a unique ID (starting from 0) which is used
	* to represent a bit in the signature. The signature is used for entities and
	* systems.
	*/
	using Signature = std::bitset<MAX_COMPONENTS>;