#include "WindowManager.h"
#include "../EntityComponentSystem/Components/Camera.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EntityComponentSystem/Coordinator.h"
#include "../AudioSystem/SoundDevice.h"
#include "../AudioSystem/SoundBuffer.h"
#include "../AudioSystem/SoundSource.h"
#include "../AudioSystem/MusicBuffer.h"

MusicBuffer* m_music;

WindowManager::WindowManager() : OgreBites::ApplicationContext("FightEngine")
{

}

bool WindowManager::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    m_p1Controller->onKeyDown(evt.keysym.sym);
    m_p2Controller->onKeyDown(evt.keysym.sym);
    return true;
}

bool WindowManager::keyReleased(const OgreBites::KeyboardEvent& evt) {
    m_p1Controller->onKeyUp(evt.keysym.sym);
    m_p2Controller->onKeyUp(evt.keysym.sym);
    return true;
}

void WindowManager::setup(void)
{
    // We first setup the base class
    OgreBites::ApplicationContext::setup();

    // Register for input events
    addInputListener(this);

    // Get a pointer to the already created root
    m_root = getRoot();
    m_sceneManager = getRoot()->createSceneManager();

    // Register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shaderGen->addSceneManager(m_sceneManager);

    SoundDevice* mySoundDevice = SoundDevice::getInstance();

    m_music = new MusicBuffer("./music.wav");

    m_music->Play();

}

void WindowManager::render() {
    getRoot()->startRendering();
}


void WindowManager::addRenderSystem(RenderSystem* renderSystem) {
    m_renderSystem = renderSystem;
}


void WindowManager::addCollisionSystem(CollisionSystem* collisionSystem) {
    m_collisionSystem = collisionSystem;
}

void WindowManager::addAnimationSystem(AnimationSystem* animSystem) {
    m_animSystem = animSystem;
}
void WindowManager::addControllerSystem(ControllerSystem* controllerSystem) {
    m_controllerSystem = controllerSystem;
}
void WindowManager::addP1Controller(Player1Controller* p1Controller) {
    m_p1Controller = p1Controller;
}
void WindowManager::addP2Controller(Player2Controller* p2Controller) {
    m_p2Controller = p2Controller;
}
void WindowManager::addMessageBus(MessageBus* msgBus) {
    m_msgBus = msgBus;
}

void WindowManager::addInputSystem(InputSystem* inputSystem)
{
    m_inputSystem = inputSystem;
}

bool WindowManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    m_inputSystem->Update(evt);
    m_renderSystem->Update(evt);
    m_collisionSystem->Update(evt);
    m_animSystem->Update(evt);
    //m_controllerSystem->Update(evt);
    m_msgBus->notify();
    m_music->UpdateBufferStream();

    return true;
}

bool WindowManager::frameEnded(const Ogre::FrameEvent& evt) {
    return true;
}
