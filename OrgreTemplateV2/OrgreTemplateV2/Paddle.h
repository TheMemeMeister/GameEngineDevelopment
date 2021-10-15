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
	SceneManager* scnMgr;
	SceneNode* paddleNode;
	float speed;
	SceneManager::PrefabType shape;
	Ogre::Vector3 Position;
	Ogre::Vector3 translate;

public:
	void CreatePaddle();
	Vector3 GetPosition();
	float SetSpeed();
	//void GetShape(prefabType);
	void Update(const Ogre::FrameEvent& evt);
	void moveLeft();
	void moveRight();
	void MakePaddleShape();
	Paddle(SceneManager* _scnMgr);
	Paddle() {}
	 ~Paddle() {}

};

