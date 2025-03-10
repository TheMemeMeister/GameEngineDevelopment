//Week14-5-AddingSwordsDemo

//Hooman Salamat

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);
float rotX = 0.0f;
float rotY = 0.0f;

bool walked = false;
Ogre::Vector3 SinbadTranslate(0, 0, 0);
//we want to move at 50 units per second 
float WalkingSpeed = 50.0f;
float SinbadRotation = 0.0f;

class ExampleFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _sceneNode;
    Ogre::SceneNode* _camNode;
    float _movementspeed;
    float _mousespeed;
    Ogre::Entity* _ent;
    Ogre::AnimationState* _aniState;
    Ogre::AnimationState* _aniStateTop;

public:

    ExampleFrameListener(Ogre::SceneNode* sceneNode, Ogre::Entity* ent, Ogre::SceneNode* camNode)
    {
        _sceneNode = sceneNode;
        _camNode = camNode;
        _movementspeed = 2.0f;
        _mousespeed = 0.002f;
       
        //step2. Then we need to change our animation states to prevent them from looping.
        //This time, we are going to control when a new animation has to start and not Ogre 3D:
        _ent = ent;
        _aniState = _ent->getAnimationState("RunBase");
        _aniState->setEnabled(true);
        _aniState->setLoop(false);

        _aniStateTop = _ent->getAnimationState("RunTop");
        _aniStateTop->setEnabled(true);
        _aniStateTop->setLoop(false);
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {

        float rotXNew = rotX * evt.timeSinceLastFrame * -1;
        float rotYNew = rotY * evt.timeSinceLastFrame * -1;


        //_camNode->yaw(Ogre::Radian(rotXNew * _mousespeed));
        //_camNode->pitch(Ogre::Radian(rotYNew * _mousespeed));
        //_camNode->moveRelative(translate * evt.timeSinceLastFrame * _movementspeed);
        _camNode->translate(translate * evt.timeSinceLastFrame * _movementspeed);

        if (walked)
        {
            _aniState->setEnabled(true);
            _aniStateTop->setEnabled(true);
            if (_aniState->hasEnded())
            {
                _aniState->setTimePosition(0.0f);
            }
            if (_aniStateTop->hasEnded())
            {
                _aniStateTop->setTimePosition(0.0f);
            }
        }
        else
        {
            _aniState->setTimePosition(0.0f);
            _aniState->setEnabled(false);
            _aniStateTop->setTimePosition(0.0f);
            _aniStateTop->setEnabled(false);
        }


        //The last thing we need to do is to apply translation and rotation to our model's scene node :
        _sceneNode->translate(SinbadTranslate * evt.timeSinceLastFrame * WalkingSpeed);
        _sceneNode->resetOrientation();
        _sceneNode->yaw(Ogre::Radian(SinbadRotation));

        _aniState->addTime(evt.timeSinceLastFrame);
        _aniStateTop->addTime(evt.timeSinceLastFrame);
                
        return true;
    }
};

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    SceneNode* mSinbadNode;
    SceneManager* mScnMgr;
    Root* mRoot;
    Ogre::PolygonMode mPolyMode;
    Camera* mCam;
    SceneNode* mCamNode;
    Entity* mSinbadEnt;
public:
    Game();
    virtual ~Game() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createScene();
    void createCamera();
    bool mouseMoved(const MouseMotionEvent& evt);
    void createFrameListener();
};


Game::Game()
    : ApplicationContext("Week14-5-AddingSwords")
{
}


void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    mRoot = getRoot();
    mScnMgr = mRoot->createSceneManager();


    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(mScnMgr);

    mPolyMode = Ogre::PolygonMode::PM_SOLID;

    createScene();
    createCamera();
    createFrameListener();
}

void Game::createScene()
{
    // -- tutorial section start --

    Ogre::SceneNode* node = mScnMgr->createSceneNode("Node1");
    mScnMgr->getRootSceneNode()->addChild(node);

    //! [turnlights]
    mScnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    mScnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
    //! [turnlights]

    //! [newlight]
    //
    Light* light1 = mScnMgr->createLight("Light1");
    light1->setType(Ogre::Light::LT_DIRECTIONAL);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 1.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    //light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = mScnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = node->createChildSceneNode("LightNode");
    lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);

    //! [newlight]

    //! [lightDirection]
    lightNode->setDirection(1, -1, 0);
    //! [lightDirection]


    //The first thing we'll do is create an abstract Plane object. This is not the mesh, it is more of a blueprint.
    Plane plane(Vector3::UNIT_Y, -10);
    //Now we'll ask the MeshManager to create us a mesh using our Plane blueprint. The MeshManager is already keeping track of the resources we loaded when initializing our application. On top of this, it can create new meshes for us.
    MeshManager::getSingleton().createPlane(
        "ground", RGN_DEFAULT,
        plane,
        1500, 1500, 200, 200,
        true,
        1, 5, 5,
        Vector3::UNIT_Z);

    //Now we will create a new Entity using this mesh.
    //We want to tell our SceneManager not to cast shadows from our ground Entity. It would just be a waste. Don't get confused, this means the ground won't cast a shadow, it doesn't mean we can't cast shadows on to the ground.
    Entity* groundEntity = mScnMgr->createEntity("ground");
    mScnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    //And finally we need to give our ground a material.
    groundEntity->setMaterialName("Examples/BeachStones");


    mSinbadEnt = mScnMgr->createEntity("Sinbad.mesh");
    mSinbadEnt->setCastShadows(true);
    mSinbadNode = mScnMgr->createSceneNode("SinbadNode");
    mSinbadNode->attachObject(mSinbadEnt);
    mScnMgr->getRootSceneNode()->addChild(mSinbadNode);
    mSinbadNode->setScale(3.0f, 3.0f, 3.0f);
    mSinbadNode->setPosition(0, 4.0, 0);

    //step1: create two instances of the sword model and name them Sword1and Sword2:
    Ogre::Entity* sword1 = mScnMgr->createEntity("Sword1", "Sword.mesh");
    Ogre::Entity* sword2 = mScnMgr->createEntity("Sword2", "Sword.mesh");
    //Now attach the sword to the model using a bone name:
    //It works if I use one of them at a time!
    //mSinbadEnt->attachObjectToBone("Handle.L", sword1);
    mSinbadEnt->attachObjectToBone("Handle.R", sword2);

}

void Game::createCamera()
{
    //! [camera]
    mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    mCam = mScnMgr->createCamera("myCam");
    mCam->setNearClipDistance(5); // specific to this sample
    mCam->setAutoAspectRatio(true);
    mCamNode->attachObject(mCam);
    mCamNode->setPosition(0, 100, 200);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(mCam);
}


void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(mSinbadNode, mSinbadEnt, mCamNode);
    mRoot->addFrameListener(FrameListener);
}


bool Game::mouseMoved(const MouseMotionEvent& evt)
{
    rotX = evt.xrel;
    rotY = evt.yrel;
    return true;
}


bool Game::keyPressed(const KeyboardEvent& evt)
{

    translate = Ogre::Vector3(0, 0, 0);
    SinbadTranslate = Ogre::Vector3(0, 0, 0);
    walked = false;

    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case SDLK_UP:
        SinbadTranslate += Ogre::Vector3(0, 0, -1);
        SinbadRotation = 3.14f;
        walked = true;
        break;
    case SDLK_DOWN:
        SinbadTranslate += Ogre::Vector3(0, 0, 1);
        SinbadRotation = 0.0f;
        walked = true;
        break;
    case SDLK_LEFT:
        SinbadTranslate += Ogre::Vector3(-1, 0, 0);
        SinbadRotation = -1.57f;
        walked = true;
        break;
    case SDLK_RIGHT:
        SinbadTranslate += Ogre::Vector3(1, 0, 0);
        SinbadRotation = 1.57f;
        walked = true;
        break;
    case 'w':
        translate += Ogre::Vector3(0, 0, -1);
        break;
    case 's':
        translate += Ogre::Vector3(0, 0, 1);
        break;
    case 'a':
        translate += Ogre::Vector3(-1, 0, 0);
        break;
    case 'd':
        translate += Ogre::Vector3(1, 0, 0);
        break;
    case 'p':
        translate = Ogre::Vector3(0, 0, 0);
        break; 
    case ' ':
        if (mPolyMode == Ogre::PolygonMode::PM_SOLID)
            mPolyMode = Ogre::PolygonMode::PM_WIREFRAME;
        else
            mPolyMode = Ogre::PolygonMode::PM_SOLID;
         mCam->setPolygonMode(mPolyMode);
        break;
    default:
        break;
    }
    return true;
}


int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [fullsource]
