#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "stdafx.h"

class Bullet : public Node {
private:
	Sprite* spr;
	PhysicsBody* body;
public:
	static Bullet* create(int bitmask);
	virtual bool init(int bitmask);

	PhysicsBody* getBody();
};

#endif // !__BULLET_H__