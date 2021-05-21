#include "WindowManager.h"

WindowManager::WindowManager() : OgreBites::ApplicationContext("FightEngine")
{
}

WindowManager::~WindowManager() {
    //TODO : destroy the pointers
}

bool WindowManager::keyPressed(const OgreBites::KeyboardEvent& evt)
{
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
    m_sceneManager = m_root->createSceneManager();

    // Register our scene with the RTSS
    m_shaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    m_shaderGen->addSceneManager(m_sceneManager);
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


bool WindowManager::frameStarted(const Ogre::FrameEvent& evt) {
    m_renderSystem->Update();
    m_collisionSystem->Update();
    return true;
}

bool WindowManager::frameEnded(const Ogre::FrameEvent& evt) {
    return true;
}
