#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>
using namespace Ogre;
using namespace OgreBites;

class Paddle

	
{
private:
	Ogre::int32 speed;
	Ogre::Vector3 pos;
	Ogre::SceneNode* paddleNode;

public:
	
	Paddle();
	Paddle(Ogre::Entity* paddleEntity, SceneManager* _scnMgr);
	~Paddle();
	 int isMouseActive;
	 Ogre::Vector3 translate;
	 Ogre::Vector3 getPosition();
	 void setPosition(Ogre::Vector3);
	 Ogre::SceneNode* getShape();
	 Ogre::int32 getSpeed();
	 void setSpeed(Ogre::int32 x);
	 void update(const Ogre::FrameEvent& evt);
	 void moveLeft();
	 void moveRight();
	 void reset();

};

