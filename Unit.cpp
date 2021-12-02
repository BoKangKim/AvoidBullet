#include "stdafx.h"
#include "Unit.h"

Unit * Unit::create(const Size & size, int bitmask, int tag)
{
	auto ret = new Unit();
	if (ret && ret->init(size, bitmask, tag)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool Unit::init(const Size & size, int bitmask, int tag)
{
	if (!Node::init ()) return false;

	body = PhysicsBody::createBox(size);
	body->setTag(tag);
	body->setCollisionBitmask(0);
	body->setContactTestBitmask(bitmask);
	addComponent(body);
	body->setRotationEnable(false);

	return true;
}

PhysicsBody * Unit::getBody()
{
	return body;
}

Player * Player::create()
{
	auto ret = new Player();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool Player::init()
{
	if (!Unit::init(Size(30, 30), PLAYER_MASK, TAG_PLAYER)) return false;

	addChild(spr = Sprite::create("res/player.png"));
	spr->setScale(0.7);

	return true;
}

Enemy * Enemy::create()
{
	auto ret = new Enemy();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool Enemy::init()
{
	if (!Unit::init(Size(30, 30), ENEMY_MASK, TAG_ENEMY)) return false;

	Sprite* enemy = Sprite::create("res/enemy.png");
	Animation* animation = Animation::create(); \
	animation->addSpriteFrameWithFile("res/enemy.png");
	animation->addSpriteFrameWithFile("res/enemy2.png");
	animation->setDelayPerUnit(0.5f);
	Animate* animate = Animate::create(animation);
	enemy->runAction(RepeatForever::create(animate));
	enemy->setScale(0.7);

	this->addChild(enemy);

	return true;
}
