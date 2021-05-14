#include "Renderer.h"

Renderer::Renderer() : OgreBites::ApplicationContext("FightEngine")
{
}

Renderer::Renderer(std::string name) : OgreBites::ApplicationContext(name) {
}


Renderer::~Renderer() {
    //TODO : destroy the pointers
}

bool Renderer::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}

void Renderer::setup(void)
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
    m_sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // We create the camera
    m_camera.cameraNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    m_camera.camera = m_sceneManager->createCamera("MainCam");
    m_camera.cameraNode->setPosition(200, 300, 400);
    m_camera.cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);
    m_camera.camera->setNearClipDistance(5);
    m_camera.cameraNode->attachObject(m_camera.camera);


    // We render it into the main window
    Ogre::Viewport* viewport = getRenderWindow()->addViewport(m_camera.camera);

    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    m_camera.camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

    // We add  a first entity
    Ogre::Entity* ninja = m_sceneManager->createEntity("ninja.mesh");
    ninja->setCastShadows(true);
    m_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ninja);

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "ground", Ogre::RGN_DEFAULT,
        plane,
        1500, 1500, 20, 20,
        true,
        1, 5, 5,
        Ogre::Vector3::UNIT_Z);
    Ogre::Entity* groundEntity = m_sceneManager->createEntity("ground");
    m_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Examples/Rockwall");

    m_sceneManager->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    m_sceneManager->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE);

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
    lightNode3->setPosition(0, 150, 250);
}

void Renderer::render() const {
    this->getRoot()->startRendering();
}

void Renderer::update() {
    // TODO: update entities
}

/**
* A function that permit to add a new entity in the renderer
*/
void Renderer::addEntity(Ogre::Entity* entity) {
    if (!m_sceneManager->getEntity(entity->getName())) {
        entity->setCastShadows(true);
        m_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entity);
        m_entities.push_back(entity);
    }
}