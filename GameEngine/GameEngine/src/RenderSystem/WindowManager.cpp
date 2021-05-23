#include "WindowManager.h"
#include "../EntityComponentSystem/Components/Camera.h"
#include "../EntityComponentSystem/Components/Transform.h"
#include "../EntityComponentSystem/Coordinator.h"

WindowManager::WindowManager() : OgreBites::ApplicationContext("FightEngine")
{
}

bool WindowManager::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    std::cout << "TEST" << std::endl;
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
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
}

void WindowManager::render() {
    getRoot()->startRendering();
}


void WindowManager::addSystem(System* system) {
    m_systems.push_back(system);
}


bool WindowManager::frameStarted(const Ogre::FrameEvent& evt) {
    for (auto system : m_systems) {
        system->Update(evt);
    }
    return true;
}

bool WindowManager::frameEnded(const Ogre::FrameEvent& evt) {
    return true;
}
