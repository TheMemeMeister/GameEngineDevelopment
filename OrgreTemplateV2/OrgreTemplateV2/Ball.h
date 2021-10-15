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
public:
	void CreateBall();
	Ball(SceneManager* _scnMgr);
	Ball() {}
	~Ball() {}

};
