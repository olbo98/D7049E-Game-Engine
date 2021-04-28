// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

#include "Ogre.h"
#include "OgreApplicationContext.h"

class Engine : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    Engine();
    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

Engine::Engine() : OgreBites::ApplicationContext("FightEngine")
{
}

bool Engine::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}

void Engine::setup(void)
{
    // We first setup the base class
    OgreBites::ApplicationContext::setup();

    // Register for input events
    addInputListener(this);

    // Get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // Register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // We add an ambient light and another one that we attach to a node
    scnMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // We create the camera
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Camera* cam = scnMgr->createCamera("MainCam");
    camNode->setPosition(200, 300, 400);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);
    cam->setNearClipDistance(5);
    camNode->attachObject(cam);


    // We render it into the main window
    Ogre::Viewport* viewport = getRenderWindow()->addViewport(cam);

    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    cam->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

    // We add  a first entity
    Ogre::Entity* ninja = scnMgr->createEntity("ninja.mesh");
    ninja->setCastShadows(true);
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ninja);
    
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "ground", Ogre::RGN_DEFAULT,
        plane,
        1500, 1500, 20, 20,
        true,
        1, 5, 5,
        Ogre::Vector3::UNIT_Z);
    Ogre::Entity* groundEntity = scnMgr->createEntity("ground");
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Examples/Rockwall");

    scnMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE);

    // SPOTLIGHT
    Ogre::Light* spotLight = scnMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(spotLight);
    lightNode->setDirection(-1, -1, 0);
    lightNode->setPosition(200, 200, 0);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    // DIRECTIONNAL LIGHT
    Ogre::Light* dirLight = scnMgr->createLight("DirectionnalLight");
    dirLight->setDiffuseColour(0.4, 0, 0);
    dirLight->setSpecularColour(0.4, 0, 0);
    dirLight->setType(Ogre::Light::LT_DIRECTIONAL);
    Ogre::SceneNode* lightNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode2->attachObject(dirLight);
    lightNode2->setDirection(0, -1, 1);

    // POINT LIGHT
    Ogre::Light* ptLight = scnMgr->createLight("PointLight");
    ptLight->setDiffuseColour(0.3, 0.3, 0.3);
    ptLight->setSpecularColour(0.3, 0.3, 0.3);
    ptLight->setType(Ogre::Light::LT_POINT);
    Ogre::SceneNode* lightNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode3->attachObject(ptLight);
    lightNode3->setPosition(0, 150, 250);

}
/*
int main(int argc, char* argv[])
{
    Engine app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}*/
