#include "Paddle.h"
Ogre::Vector3 translate(0, 0, 0);


void Paddle::CreatePaddle()
{
	MakePaddleShape();
	paddleNode->setPosition(0, -10, 0);
	paddleNode->setScale(0.2f, 0.05f, 1.0f);
	translate = Ogre::Vector3(0, 0, 0);

}
Vector3 Paddle::GetPosition()
{
	return paddleNode->getPosition();
	
}

void Paddle::Update(const Ogre::FrameEvent& evt)
{
	GetPosition();
	paddleNode->translate(translate * evt.timeSinceLastFrame);
	//translate = _translate;

}

void Paddle::moveLeft()
{
	if (paddleNode->getPosition().x > -102)
		translate = Ogre::Vector3(-30, 0, 0);
}

void Paddle::moveRight()
{
	if (paddleNode->getPosition().x < 102)
		translate = Ogre::Vector3(30, 0, 0);
}

void Paddle::MakePaddleShape()
{
	Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);
	paddleNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	paddleNode->attachObject(paddleEntity);
}

Paddle::Paddle(SceneManager* _scnMgr)
	
{

	scnMgr = _scnMgr;
	CreatePaddle();
	
	
}