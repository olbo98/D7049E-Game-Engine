#pragma once
#include "../Utils/Utils.h"
#include "../EventSystem/System.h"
#include "OgreApplicationContext.h"

class RenderSystem : public System{
public:
	void Init();

	void Update();

	void handleMessage(Message* msg);

	//TODO: permits to change light color ?
	/**
	* Function that permits to add a spot light in the scene
	* @param position position of the light
	* @param direction direction of the light
	* @param name name of the light
	*/
	void addSpotLight(Vec3 position, Vec3 direction, std::string name = "SpotLight");

	/**
	* Function that permits to add a point light in the scene
	* @param position position of the light
	* @param name name of the light
	*/
	void addPointLight(Vec3 position, std::string name = "PointLight");

	/**
	* Function that permits to add a direction light in the scene
	* @param position position of the light
	* @param direction direction of the light
	* @param name name of the light
	*/
	void addDirectionLight(Vec3 position, Vec3 direction, std::string name = "DirLight");

private:
	Entity m_camera;
};
