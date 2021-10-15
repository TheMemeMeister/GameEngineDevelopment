#pragma once

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
#include "Paddle.h"
#include "Ball.h"

using namespace Ogre;
using namespace OgreBites;
Ogre::int32 isCollide;
Ogre::int32 movDirY;
Ogre::int32 movDirX;
Ogre::int32 score = 0;
Ogre::int32 lives = 3;


class ExampleFrameListener : public Ogre::FrameListener
{
private:
    Paddle* gamepaddle;
    Ball* gameball;
    Ogre::Vector3 btranslate;
    
public:

    ExampleFrameListener(Paddle* paddle, Ball* ball)
    {
        gamepaddle = paddle;
        gameball = ball;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
       /* _node->translate(translate * evt.timeSinceLastFrame);
        translate = Ogre::Vector3(0, 0, 0);*/
         //btranslate = Ogre::Vector3(-10*movDirX, -10 * movDirY, 0);
         //gameball->translate(btranslate * evt.timeSinceLastFrame);
        //gamepaddle -> Update(evt);
        //btranslate = Ogre::Vector3(-10 * movDirX, -10 * movDirY, 0);
        //ball->translate(btranslate * evt.timeSinceLastFrame);

        return true;
    }
    
};

class Game
    : public ApplicationContext
    , public InputListener
{
private: 
    SceneNode* paddleNode;
    Paddle* paddle;
    Ball* ball;
    SceneNode* ballNode;
       SceneManager* scnMgr;
       OgreBites::TrayManager* mTrayMgr;
       Root* root;
       Ogre::FrameListener* FrameListener;
       bool gameover = false;
       int nof = 0;
       float time = 0;
       float fr = 0;
       float rt = 0.03;
public:
    Game();
    virtual ~Game() {}

    void setup();
    //bool keyPressed(const KeyboardEvent& evt);
    bool mouseMoved(const MouseMotionEvent& evt) override;
    bool frameRenderingQueued(const FrameEvent& evt);
    void createScene();
    void createCamera();
    void createFrameListener(Paddle* paddle, Ball* ball);
    OgreBites::TrayListener myTrayListener;
    OgreBites::Label* mInfoLabel;
    OgreBites::Label* mScoreLabel;
    OgreBites::Label* mScore;
    OgreBites::Label* mLivesLabel;
    OgreBites::Label* mLives;
    OgreBites::Label* mFPS;
    OgreBites::Label* mTPU;
    OgreBites::Button* mQuitBtn = nullptr;
    OgreBites::Label* mGameOverLabel;

    Ogre::DisplayString sc;
    Ogre::DisplayString l;
    Ball* mBall;
    Paddle* mPaddle;
};

Game::Game()
    : ApplicationContext("Game Engine Development Assignment 1")
{
    score = 0;
    lives = 3;
    isCollide = 0;//no collision
    movDirY = 1;

    movDirX = 0;// Ogre::Math::RangeRandom(-1, 1);
    mBall = nullptr;
    bool gameover = false;

}

void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
     root = getRoot();
     scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    createScene();
    createCamera();
    createFrameListener(paddle,ball);
}


//bool Game::keyPressed(const KeyboardEvent& evt)
//{
//    
//    switch (evt.keysym.sym)
//    {
//        
//    case SDLK_ESCAPE:
//        getRoot()->queueEndRendering();
//        break;
//
//    case 'a':
//    case SDLK_LEFT:
//        paddle->moveLeft();
//        break;
//    case 'd':
//    case SDLK_RIGHT:
//        paddle->moveRight();
//        break;
//    default:
//        break;
//    }
//    
//    return true;
//}

bool Game::mouseMoved(const MouseMotionEvent& evt)
{
    /* Pause game when the game is over*/
    

    float mtw = (evt.x - (float)getRenderWindow()->getWidth() / 2.0f) * 0.5f;

    paddleNode->setPosition(Vector3(mtw, -10.f, 0.f));
    return true;
}
void Game::createScene()
{
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


    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());

    //you must add this in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);
    //Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);

    mTrayMgr->showLogo(TL_TOPRIGHT);
    // mTrayMgr->showFrameStats(TL_TOPRIGHT);
     //mTrayMgr->toggleAdvancedFrameStats();
    sc = std::to_string(score);
    l = std::to_string(lives);
    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "Ping Pong Game", 350);
    mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
    mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", sc, 150);
    mLivesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
    mLives = mTrayMgr->createLabel(TL_TOPLEFT, "lives", l, 150);
    mFPS = mTrayMgr->createLabel(TL_TOPRIGHT, "FPS", "FPS: 60", 150);
    mTPU = mTrayMgr->createLabel(TL_TOPRIGHT, "TPU", "Time/Update: 0m/s", 200);
    
    // a friendly reminder
    //StringVector names;
    //names.push_back("Help");
    //mTrayMgr->createParamsPanel(TL_TOPLEFT, "Help", 100, names)->setParamValue(0, "H/F1");


    Ogre::Entity* ballEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
    mBall = new Ball(ballEntity, scnMgr);
    ballNode = mBall->getShape();

   /* Paddle paddleTemp = Paddle(scnMgr);
    paddle = &paddleTemp;*/
    //paddle = new Paddle(scnMgr);
    Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);
  

    mPaddle = new Paddle(paddleEntity, scnMgr);
    paddleNode = mPaddle->getShape();
    //Ogre::SceneNode* 
    
    //Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);
    ////Ogre::SceneNode* 
    //paddleNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    //paddleNode->setPosition(0, -10, 0);
    //paddleNode->setScale(0.2f, 0.05f, 1.0f);
    //paddleNode->attachObject(paddleEntity);

    scnMgr->showBoundingBoxes(true);

}
void Game::createCamera()
{
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

}


void Game::createFrameListener(Paddle* paddle, Ball* ball)
{
    FrameListener = new ExampleFrameListener(paddle, ball);
    mRoot->addFrameListener(FrameListener);
    
}

bool Game::frameRenderingQueued(const FrameEvent& evt)
{
    mBall->update(evt);
    mPaddle ->update(evt);
    if (time < rt)
    {
        time += evt.timeSinceLastFrame;
        nof++;
    }
    else
    {
        fr = (float)nof / time;
        nof = 0;
        time = 0;
        char str[20];
        sprintf_s(str, "FPS: %.1f", fr);
        mFPS->setCaption(str);
    }
    char str1[80];
    sprintf_s(str1, "Time/Update: %.3f m/s", evt.timeSinceLastFrame);
    mTPU->setCaption(str1);
    if (gameover)
    {

        if (mQuitBtn->getState() == OgreBites::ButtonState::BS_DOWN)
        {
            getRoot()->queueEndRendering();
        }
        return true;
    }
    else
    {
        if (ballNode->getPosition().y < -50)
        {
            //std::cout << "ball fall" << std::endl;
            if (lives > 0)
            {
                lives--;
                l = std::to_string(lives);
                mLives->setCaption(l);
                ballNode->setPosition(Ogre::Vector3(0, 100, 0));
                std::cout << "lives:" << lives << std::endl;
                mBall->reset();
            }
            else
            {
                mGameOverLabel = mTrayMgr->createLabel(TL_CENTER, "gameO", "GAME OVER!", 150);
                mQuitBtn = mTrayMgr->createButton(TL_CENTER, "qbtn", "Quit Game", 150);
                gameover = true;
            }

        }
        //collision
        AxisAlignedBox spbox = ballNode->_getWorldAABB();
        AxisAlignedBox cbbox = paddleNode->_getWorldAABB();
        if (spbox.intersects(cbbox))
        {
            if (isCollide == 0)
            {
                std::cout << "collide";
                isCollide = 1;
                movDirY = -1;
                mBall->setVelY(-1);
                score++;
                sc = std::to_string(score);
                mScore->setCaption(sc);
                std::cout << "score:" << score << std::endl;
                // btranslate = Ogre::Vector3(0, 10, 0);
                const auto attackVector = ballNode->getPosition() - paddleNode->getPosition();
                const auto normal = Ogre::Vector3(0, -1, 0);

                const auto dot = attackVector.dotProduct(normal);
                const auto angle = acos(dot / attackVector.length()) * Ogre::Math::fRad2Deg;

                if ((attackVector.x > 0 && attackVector.y > 0) || (attackVector.x < 0 && attackVector.y > 0))
                    // bottom right or bottom left
                {
                    //angle = 140;
                    if (angle <= 135)
                    {
                        //object1->getRigidBody()->velocity = glm::vec2(-velocityX, velocityY);
                        movDirX = 1;
                        movDirY = -1;
                        mBall->setVelY(-1);
                        mBall->setVelX(1);
                        std::cout << "bottom right" << std::endl;
                    }
                    else
                    {
                        // object1->getRigidBody()->velocity = glm::vec2(velocityX, -velocityY);
                        movDirY = -1;
                        movDirX = -1;
                        mBall->setVelY(-1);
                        mBall->setVelX(-1);
                        std::cout << "bottom left" << std::endl;
                    }
                }
            }

        }
        else
            isCollide = 0;

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
