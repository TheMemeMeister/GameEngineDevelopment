/*-------------------------------------------------------------------------
//To use Trays, you have to create an TrayManager. This is the class through which you will create and 
//manage all your widgets, manipulate the cursor, change the backdrop image, adjust tray properties, 
//pop up dialogs, show/hide the loading bar, etc. You can have multiple tray managers in one application.
-------------------------------------------------------------------------*/

//! [fullsource]

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;
Ogre::Vector3 translate(0, 0, 0);

class ExampleFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _node;
    Ogre::SceneNode* _node2;
    
public:

    ExampleFrameListener(Ogre::SceneNode* paddle, Ogre::SceneNode* ball)
    {
        _node = paddle;
         _node2 = ball;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        _node->translate(translate * evt.timeSinceLastFrame);
        translate = Ogre::Vector3(0, 0, 0);
        _node2->translate(Ogre::Vector3(0, -1.0f, 0) * evt.timeSinceLastFrame);
       
        return true;
    }
    
};

class BasicTutorial1
    : public ApplicationContext
    , public InputListener
{
private: 
    SceneNode* paddleNode;
    SceneNode* ballNode;
       SceneManager* scnMgr;
       Root* root;
       Ogre::FrameListener* FrameListener;
public:
    BasicTutorial1();
    virtual ~BasicTutorial1() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    //void createScene();
    void createFrameListener();
    void FrameUpdate();
    OgreBites::TrayListener myTrayListener;
    OgreBites::Label* mInfoLabel;
};

BasicTutorial1::BasicTutorial1()
    : ApplicationContext("Game Engine Development Assignment 1")
{
}

void BasicTutorial1::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(20, 80, 50);
    //! [lightpos]

    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
    //! [camera]


    //! [cameramove]
    camNode->setPosition(0, 47, 222);
    //! [cameramove]


    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());

    //you must add this in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);
    //Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);
    
    mTrayMgr->showLogo(TL_TOPRIGHT);
    mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
    //mTrayMgr->toggleAdvancedFrameStats();

    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "Ping Pong Game", 350);

    // a friendly reminder
    StringVector names;
    names.push_back("Help");
    mTrayMgr->createParamsPanel(TL_TOPLEFT, "Help", 100, names)->setParamValue(0, "H/F1");


    Ogre::Entity* ballEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
    ballNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    ballNode->setPosition(0,0,0);
    ballNode->setScale(0.2f, 0.2f, 0.2f);
    ballNode->attachObject(ballEntity);

    Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);
    paddleNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    paddleNode->setPosition(  0,-10,0);
    paddleNode->setScale(0.2f, 0.05f, 1.0f);
    paddleNode->attachObject(paddleEntity);

    scnMgr->showBoundingBoxes(true);
    

    // -- tutorial section end --
    createFrameListener();
}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)//moving paddle
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
   /* case 'w':
        translate = Ogre::Vector3(0, 0, -10);
        break;
    case 's':
        translate = Ogre::Vector3(0, 0, 10);
        break;*/
    case 'a':
        translate = Ogre::Vector3(-10, 0, 0);
        break;
    case 'd':
        translate = Ogre::Vector3(10, 0, 0);
        break;
    default:
        break;
    }
    return true;
}
void BasicTutorial1::FrameUpdate() {
    //Move ball here
}

void BasicTutorial1::createFrameListener()
{
    FrameListener = new ExampleFrameListener(paddleNode, ballNode);
    mRoot->addFrameListener(FrameListener);
    
}



int main(int argc, char** argv)
{
    try
    {
        BasicTutorial1 app;
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
