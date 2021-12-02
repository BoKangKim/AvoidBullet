#include "stdafx.h"
#include "EnemyBulletComponent.h"
#include "SceneIngame.h"
#include "Bullet.h"
#include "Unit.h"

EnemyAttackRoutine * EnemyAttackRoutine::create(EnemyAttackType t)
{
	auto ret = new EnemyAttackRoutine();
	if (ret && ret->init(t)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool EnemyAttackRoutine::init(EnemyAttackType t)
{
	if (!Component::init()) return false;

	this->type = t;
	this->setName("EnemyAttack");

	return true;
}

void EnemyAttackRoutine::update(float dt)
{
	switch (this->type) {
	case EnemyAttackType::EASY: logic_easy(dt); break;
	case EnemyAttackType::NORMAL: logic_normal(dt); break;
	case EnemyAttackType::DIFFICULT: logic_difficult(dt); break;
	}
}

void EnemyAttackRoutine::logic_easy(float dt)
{
	elapsed += dt;

	if (elapsed > 1.0f) {
		elapsed = 0.0;
		for (int i = 0; i < 4; i++) {
			int radian = rand() % 60 - 30;
			createBulletAndGo(EASY_BULLET_SPEED, radian);
		}
	
	}
}

void EnemyAttackRoutine::logic_normal(float dt)
{
	elapsed += dt;

	if (elapsed > 0.8f) {
		elapsed = 0.0;
			for (int i = 0; i < 5; i++){
				int radian = rand() % 60 - 30;
				createBulletAndGo(NORMAL_BULLET_SPEED, radian);
		}
		

	}
}

void EnemyAttackRoutine::logic_difficult(float dt)
{
	elapsed += dt;

	if (elapsed > 0.5f) {
		elapsed = 0.0;
		for (int i = 0; i < 10; i++) {
			int radian = rand() % 60 - 30;
			createBulletAndGo(DIFFICULT_BULLET_SPEED, radian);
		}
	
	}
}

void EnemyAttackRoutine::createBulletAndGo(float speed, float delta_angle)
{
	SceneIngame* scene = (SceneIngame*)Director::getInstance()->getRunningScene();
	auto player = scene->getPlayer();
	if (player == nullptr) return;

	auto bullet = Bullet::create(ENEMY_BULLET_MASK);
	bullet->setPosition(getOwner()->getPosition());
	scene->addChild(bullet);

	Vec2 pos = player->getPosition() - getOwner()->getPosition();
	pos = pos.getNormalized() * speed;
	pos = pos.rotateByAngle(Vec2::ZERO, GET_RAD(delta_angle));
	bullet->getBody()->setVelocity(pos);

	if (type == EnemyAttackType::EASY) {
		bullet->runAction(Sequence::create(DelayTime::create(4.5f), RemoveSelf::create(), nullptr));
	}
	if (type == EnemyAttackType::NORMAL) {
		bullet->runAction(Sequence::create(DelayTime::create(4.0f), RemoveSelf::create(), nullptr));
	}
	if (type == EnemyAttackType::DIFFICULT) {
		bullet->runAction(Sequence::create(DelayTime::create(3.7f), RemoveSelf::create(), nullptr));
	}
}


