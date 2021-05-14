#pragma once
#include "EntityComponentDef.h"
#include<set>

/**
* CLASS SYSTEM
* A System contains any functionality that iterates upon a list of entities
* with a certain signature of components.
*/
class System
{
public:
	std::set<Entity> m_entities;
};
