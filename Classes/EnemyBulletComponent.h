#pragma once
#ifndef __ENEMY_COMPONENT_H__
#define __ENEMY_COMPONENT_H__

#include "stdafx.h"
#include "Unit.h"

enum class EnemyAttackType {
	EASY, NORMAL, DIFFICULT
};

class EnemyAttackRoutine : public Component {
private:
	EnemyAttackType type;
	float elapsed = 0;
	static long long stscore;
	char scoreString[128];
public:
	static EnemyAttackRoutine* create(EnemyAttackType t);
	virtual bool init(EnemyAttackType t);

	virtual void update(float dt);

	void logic_easy(float dt);
	void logic_normal(float dt);
	void logic_difficult(float dt);

	void createBulletAndGo(float speed, float delta_angle);

};

#endif // !__ENEMY_COMPONENT_H__