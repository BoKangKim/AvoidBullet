#pragma once
#ifndef __UNIT_H__
#define __UNIT_H__
#include "stdafx.h"

class Unit : public Node {
private:
protected:
	PhysicsBody* body;
	Sprite* spr;
public:
	static Unit* create(const Size& size, int bitmask, int tag);
	virtual bool init(const Size& size, int bitmask, int tag);
	PhysicsBody* getBody();
};

class Player : public Unit {
public:
	static Player* create();
	virtual bool init();
};

class Enemy : public Unit {
public:
	static Enemy* create();
	virtual bool init();
};
#endif // !__UNIT_H__
