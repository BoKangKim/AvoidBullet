#pragma once
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#define DEBUG_MODE false
#define EASY_BULLET_SPEED 300
#define NORMAL_BULLET_SPEED 400
#define DIFFICULT_BULLET_SPEED 550

// 1(2)
#define PLAYER_MASK 0x00000001

// 0(2)
#define ENEMY_MASK 0x00000000

// 1(2);
#define ENEMY_BULLET_MASK 0x00000001

#define TAG_PLAYER 1
#define TAG_ENEMY 2
#define TAG_ENEMY_BULLET 3

#define PLAYER_MOVEMENT_SPEED 600

#define PI 3.14159265358
#define GET_RAD(X) (X*(PI/180.0))
#define FONT_NAME "fonts/SDSamliphopangcheTTFBasic.ttf"

#endif