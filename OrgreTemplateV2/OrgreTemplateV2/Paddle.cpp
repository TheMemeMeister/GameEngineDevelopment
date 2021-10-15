
#include "Paddle.h"

void Paddle::reset()
{
	translate = Ogre::Vector3(0, 0, 0);
	isMouseActive = false;
}

Paddle::Paddle()
{

}

Paddle::Paddle(Ogre::Entity* ent, Ogre::SceneManager* scnMgr)
{
	paddleNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	paddleNode->setPosition(0, -10, 0);
	paddleNode->setScale(0.2f, 0.05f, 1.0f);
	paddleNode->attachObject(ent);
	reset();

	pos = paddleNode->getPosition();
}


Ogre::Vector3 Paddle::getPosition()
{
	return pos;
}

void Paddle::setPosition(Ogre::Vector3 p)
{
	pos = p;
}

Ogre::SceneNode* Paddle::getShape()
{
	return paddleNode;
}

Ogre::int32 Paddle::getSpeed()
{
	return speed;
}

void Paddle::setSpeed(Ogre::int32 x)
{
	speed = x;
}

void Paddle::update(const Ogre::FrameEvent& evt)
{
	if (isMouseActive)
	{
		if (pos.x > 102)
			pos.x = 102;
		if (pos.x < -102)
			pos.x = -102;
		paddleNode->setPosition(pos);
	}
	else
	{
		paddleNode->translate(translate * evt.timeSinceLastFrame);
		translate = Ogre::Vector3(0, 0, 0);
	}
}

void Paddle::moveLeft()
{
	if (paddleNode->getPosition().x > -102 && !isMouseActive)
		translate = Ogre::Vector3(-30, 0, 0);
}

void Paddle::moveRight()
{
	if (paddleNode->getPosition().x < 102 && !isMouseActive)
		translate = Ogre::Vector3(30, 0, 0);
}