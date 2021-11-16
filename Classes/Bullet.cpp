#include "stdafx.h"
#include "Bullet.h"

Bullet * Bullet::create(int bitmask)
{
	auto ret = new Bullet();
	if (ret && ret->init(bitmask)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool Bullet::init(int bitmask)
{
	if (!Node::init()) return false;
	body = PhysicsBody::createCircle(5.0);
	body->setCollisionBitmask(0);
	body->setContactTestBitmask(bitmask);
	body->setTag(TAG_ENEMY_BULLET);
	addComponent(body);
	addChild(spr = Sprite::create("res/bullet.png"));
	spr->setScale(0.3);
	return true;
}

PhysicsBody * Bullet::getBody()
{
	return this->body;
}
