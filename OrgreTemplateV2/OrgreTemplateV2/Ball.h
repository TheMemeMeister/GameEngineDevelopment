#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>
using namespace Ogre;
using namespace OgreBites;
class Ball


{
private:
	SceneManager* scnMgr;
	SceneNode* BallNode;
	float speed;
	SceneManager::PrefabType shape;
	Ogre::Vector3 Position;
	Ogre::Vector3 btranslate;
	Ogre::Vector3 Velocity;
public:
	void CreateBall();
	Ball(SceneManager* _scnMgr);
	Vector3 GetPosition();
	//void GetShape(prefabType);
	void Update(const Ogre::FrameEvent& evt);
	void moveLeft();
	void moveRight();
	void MakeBallShape();
	float setBallxVelocity();
	float setBallyVelocity();
	Ball() {}
	~Ball() {}

};
