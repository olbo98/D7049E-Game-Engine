// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

/*#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "EventSystem/MessageBus.h"
#include "EventSystem/System.h"
#include "AnimationSystem/AnimationSystem.h"

class MyTestApp : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    MyTestApp();
    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

    Ogre::Entity* ent;
    Ogre::AnimationState* topAnim;
    Ogre::AnimationState* middleAnim;
};

//! [constructor]
MyTestApp::MyTestApp() : OgreBites::ApplicationContext("OgreTutorialApp")
{
}
//! [constructor]

//! [key_handler]
bool MyTestApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}
//! [key_handler]

//! [setup]
void MyTestApp::setup(void)
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    // finally something to render
    ent = scnMgr->createEntity("Sinbad.mesh");
    //ent->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
    topAnim = ent->getAnimationState("JumpStart");
    topAnim->setLoop(false);
    topAnim->setEnabled(true);
    middleAnim = ent->getAnimationState("JumpLoop");
    middleAnim->setLoop(false);
    middleAnim->setEnabled(false);

    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
}

bool MyTestApp::frameRenderingQueued(const Ogre::FrameEvent& fe) {
    if (!topAnim->hasEnded()) {
        topAnim->setEnabled(true);
        middleAnim->setEnabled(false);
        topAnim->addTime(fe.timeSinceLastFrame);
    }
    else {
        topAnim->setEnabled(false);
        middleAnim->setEnabled(true);
        middleAnim->addTime(fe.timeSinceLastFrame);
    }
    
    return true;
}*/

//! [setup]
#include "EventSystem/MessageBus.h"
#include "AnimationSystem/AnimationSystem.h"

//! [main]
int main(int argc, char* argv[])
{
    /*MyTestApp app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;*/
    MessageBus* msgBus = new MessageBus();
    //-AnimationSystem* animSys = new AnimationSystem(msgBus);
    //msgBus->addReciever(animSys);
    //int num = 10;
    //TestMessage* testMsg = new TestMessage(&num);
    //msgBus->postMessage(testMsg);
    //msgBus->notify();
}
//! [main]
