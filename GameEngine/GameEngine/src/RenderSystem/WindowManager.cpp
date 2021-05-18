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

    // We add an ambient light and another one that we attach to a node
    //m_sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));


    /*
    // SPOTLIGHT
    Ogre::Light* spotLight = m_sceneManager->createLight("SpotLight");
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    Ogre::SceneNode* lightNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(spotLight);
    lightNode->setDirection(-1, -1, 0);
    lightNode->setPosition(200, 200, 0);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    // DIRECTIONNAL LIGHT
    Ogre::Light* dirLight = m_sceneManager->createLight("DirectionnalLight");
    dirLight->setDiffuseColour(0.4, 0, 0);
    dirLight->setSpecularColour(0.4, 0, 0);
    dirLight->setType(Ogre::Light::LT_DIRECTIONAL);
    Ogre::SceneNode* lightNode2 = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode2->attachObject(dirLight);
    lightNode2->setDirection(0, -1, 1);

    // POINT LIGHT
    Ogre::Light* ptLight = m_sceneManager->createLight("PointLight");
    ptLight->setDiffuseColour(0.3, 0.3, 0.3);
    ptLight->setSpecularColour(0.3, 0.3, 0.3);
    ptLight->setType(Ogre::Light::LT_POINT);
    Ogre::SceneNode* lightNode3 = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode3->attachObject(ptLight);
    lightNode3->setPosition(0, 150, 250);*/
}

void WindowManager::render() const {
    this->getRoot()->startRendering();
}


void WindowManager::addRenderSystem(RenderSystem* renderSystem) {
    m_renderSystem = renderSystem;
}


bool WindowManager::frameStarted(const Ogre::FrameEvent& evt) {
    m_renderSystem->Update();
    return true;
}

bool WindowManager::frameEnded(const Ogre::FrameEvent& evt) {
    return true;
}
