#include "WindowManager.h"
#include "../AudioSystem/SoundDevice.h"
#include "../AudioSystem/SoundBuffer.h"
#include "../AudioSystem/SoundSource.h"
#include "../AudioSystem/MusicBuffer.h"

MusicBuffer* m_music;

WindowManager::WindowManager() : OgreBites::ApplicationContext("FightEngine")
{

}

WindowManager::~WindowManager() {
    //TODO : destroy the pointers
}

bool WindowManager::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    //std::cout << evt.keysym.sym << std::endl;
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    m_controllerSystem->onKeyDown(evt.keysym.sym);
    return true;
}

bool WindowManager::keyReleased(const OgreBites::KeyboardEvent& evt) {
    m_controllerSystem->onKeyUp(evt.keysym.sym);
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
    m_sceneManager = m_root->createSceneManager();

    // Register our scene with the RTSS
    m_shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    m_shaderGen->addSceneManager(m_sceneManager);

    SoundDevice* mySoundDevice = SoundDevice::getInstance();

    m_music = new MusicBuffer("./music.wav");

    m_music->Play();

}

void WindowManager::render() const {
    this->getRoot()->startRendering();
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
void WindowManager::addMessageBus(MessageBus* msgBus) {
    m_msgBus = msgBus;
}

void WindowManager::addInputSystem(InputSystem* inputSystem)
{
    m_inputSystem = inputSystem;
}


bool WindowManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    m_inputSystem->update();
    m_renderSystem->Update();
    m_collisionSystem->Update();
    m_animSystem->Update(evt);
    m_controllerSystem->Update();
    m_msgBus->notify();
    m_music->UpdateBufferStream();
    return true;
}

bool WindowManager::frameEnded(const Ogre::FrameEvent& evt) {
    return true;
}
