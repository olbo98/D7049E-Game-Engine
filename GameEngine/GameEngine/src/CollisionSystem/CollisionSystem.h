#pragma once
#include "../Utils/Utils.h"
#include "../EventSystem/System.h"
#include "OgreApplicationContext.h"

class CollisionSystem : public System {
public:
	void Init();

	void Update();

	/**
	* Function that gives the world position of the collider given the world position of the entity 
	* and the relative position of the collider to the transform
	* @param transPos world position of the entity
	* @param relativePos relative position of the collider to the transform
	* @return Vec3 : the world position of the collider
	*/
	Vec3 getColliderPos(Vec3 transPos, Vec3 relativePos);

	/**
	* Function that checks if 2 entities collide 
	* Based on the theory of this page : https://www.euclideanspace.com/threed/animation/collisiondetect/index.htm
	* @param pos1 the pos of the first entity
	* @param pos2 the pos of the second entity
	* @param size1 the size of the first entity
	* @param size2 the size of the second entity
	* @return bool : true if there's a collision, false if not
	*/
	bool doCollide(Vec3 pos1, Vec3 pos2, Vec3 size1, Vec3 size2);

	virtual void handleMessage(Message* msg);
};