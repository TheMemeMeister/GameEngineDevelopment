#include "Ball.h"
Ball::Ball()
{
}
Ball::Ball(Ogre::Entity* ent, Ogre::SceneManager* scnMgr)
{
	ball = scnMgr->getRootSceneNode()->createChildSceneNode();
	ball->setPosition(0, 100, 0);
	ball->setScale(0.1f, 0.1f, 0.1f);

	ball->attachObject(ent);
	reset();

	pos = ball->getPosition();

}
Ball::~Ball()
{
}
void Ball::reset() {
	velY = 1;

	velX = 0;
	btranslate = Ogre::Vector3(0, 0, 0);
}
Ogre::Vector3 Ball::getPosition()
{
	return pos;
}
void Ball::setPosition(Ogre::Vector3 p)
{
	pos = p;
}

Ogre::SceneNode* Ball::getShape()
{
	return ball;
}

Ogre::int32 Ball::getVelX()
{
	return velX;
}

void Ball::setVelX(Ogre::int32 x)
{
	velX = x;
}

Ogre::int32 Ball::getVelY()
{
	return velY;
}
void Ball::setVelY(Ogre::int32 y)
{
	velY = y;
}
void Ball::update(const Ogre::FrameEvent& evt)
{
	btranslate = Ogre::Vector3(-10 * velX, -10 * velY, 0);
	//moving ball
	if (ball->getPosition().y > 135)
	{
		velY = 1;
	}

	if (ball->getPosition().x > 112)
	{
		velX = 1;
		// std::cout << "greater then 112" << std::endl;
	}
	if (ball->getPosition().x < -112)
	{
		//std::cout << "less then -112" << std::endl;
		velX = -1;
	}
	ball->translate(btranslate * evt.timeSinceLastFrame);
}