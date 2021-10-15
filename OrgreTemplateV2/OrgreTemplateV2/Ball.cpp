#include "Ball.h"
Ogre::Vector3 btranslate(0, 0, 0);

void Ball::CreateBall ()
{
	Ogre::Entity* BallEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
	//Ogre::SceneNode* 
	BallNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	BallNode->setPosition(0, -100, 0);
	BallNode->setScale(0.1f, 0.1f, 0.1f);
	BallNode->attachObject(BallEntity);
}
Vector3 Ball::GetPosition()
{
	return BallNode->getPosition();

}

void Ball::Update(const Ogre::FrameEvent& evt)
{
	GetPosition();
	BallNode->translate(btranslate * evt.timeSinceLastFrame);
	//translate = _translate;

}




void Ball::MakeBallShape()
{
	Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
	BallNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	BallNode->attachObject(paddleEntity);
}

Ball::Ball(SceneManager* _scnMgr)

{

	scnMgr = _scnMgr;
	CreateBall();


}