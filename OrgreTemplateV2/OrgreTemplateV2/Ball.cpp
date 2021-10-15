#include "Ball.h"


void Ball::CreateBall ()
{
	Ogre::Entity* BallEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
	//Ogre::SceneNode* 
	BallNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	BallNode->setPosition(0, -10, 0);
	BallNode->setScale(0.2f, 0.05f, 1.0f);
	BallNode->attachObject(BallEntity);
}

Ball::Ball(SceneManager* _scnMgr)

{

	scnMgr = _scnMgr;
	CreateBall();


}