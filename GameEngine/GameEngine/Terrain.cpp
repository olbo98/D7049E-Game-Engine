// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT
/*
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

    Ogre::Vector3 terrainPos(0, 0, 0);

    // We create the camera
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Camera* cam = scnMgr->createCamera("MainCam");
    camNode->setPosition(terrainPos + Ogre::Vector3(1638, 50, 2116));
    camNode->lookAt(Ogre::Vector3(1963, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);
    cam->setNearClipDistance(40);
    cam->setFarClipDistance(0);
    camNode->attachObject(cam);


    // We render it into the main window
    Ogre::Viewport* viewport = getRenderWindow()->addViewport(cam);

    Ogre::Light* light = scnMgr->createLight();
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setDirection(Ogre::Vector3(0.55, -0.3, 0.75).normalisedCopy());
    lightNode->attachObject(light);

}
int main(int argc, char* argv[])
{
    Engine app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}*/
