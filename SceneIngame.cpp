#include "stdafx.h"
#include "Sceneingame.h"
#include "Unit.h"
#include "EnemyBulletComponent.h"
#include "SceneHome.h"
#include <string>

SceneIngame * SceneIngame::create(int level)
{
	auto ret = new SceneIngame();
	if (ret && ret->init(level)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool SceneIngame::init(int level)
{
	if (!Scene::initWithPhysics()) return false;

	auto world = getPhysicsWorld();
	if (DEBUG_MODE) world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	world->setGravity(Vec2::ZERO);

	set_level(level);
	auto keybd = EventListenerKeyboard::create();
	keybd->onKeyPressed = std::bind(&SceneIngame::onKeyPressed, this, std::placeholders::_1, std::placeholders::_2);
	keybd->onKeyReleased = std::bind(&SceneIngame::onKeyReleased, this, std::placeholders::_1, std::placeholders::_2);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keybd, this);

	auto contact = EventListenerPhysicsContact::create();
	contact->onContactBegin = std::bind(&SceneIngame::onContactBegin, this, std::placeholders::_1);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contact, this);

	schedule(CC_SCHEDULE_SELECTOR(SceneIngame::logic));

	return true;
}

void SceneIngame::onEnter()
{
	Scene::onEnter();

	EnemyAttackType levelType = EnemyAttackType::NORMAL;
	if (level == 0) {
		levelType = EnemyAttackType::EASY;
	}
	else if (level == 1) {
		levelType = EnemyAttackType::NORMAL;
	}
	else if (level == 2) {
		levelType = EnemyAttackType::DIFFICULT;
	}
	
	{
		auto enemy = Enemy::create();
		enemy->setPosition(Vec2(0 + 15,720 - 15));
		enemy->addComponent(EnemyAttackRoutine::create(levelType));
		addChild(enemy);
	}
	{
		auto enemy = Enemy::create();
		enemy->setPosition(Vec2(0 + 15, 0 + 15));
		enemy->addComponent(EnemyAttackRoutine::create(levelType));
		addChild(enemy);
	}
	{
		auto enemy = Enemy::create();
		enemy->setPosition(Vec2(1280 - 15, 0 + 15));
		enemy->addComponent(EnemyAttackRoutine::create(levelType));
		addChild(enemy);
	}
	{
		auto enemy = Enemy::create();
		enemy->setPosition(Vec2(1280 - 15, 720 - 15));
		enemy->addComponent(EnemyAttackRoutine::create(levelType));
		addChild(enemy);
	}
	initUI();
	hideOverPanel();
	player = Player::create();
	player->setPosition(Vec2(1280 / 2, 720 / 2));
	addChild(player);
}

void SceneIngame::initUI()
{
	addChild(overPanel = Scale9Sprite::create("res/panel.png"));
	overPanel->setPosition(Vec2(1280 / 2, 720 / 2));
	overPanel->setScale9Enabled(true);
	overPanel->setContentSize(Size(600, 400));

	overPanel->addChild(btnHome = Button::create("res/button_blue.png", "res/button_yellow.png", "res/button_grey.png"));
	overPanel->addChild(btnQuit = Button::create("res/button_blue.png", "res/button_yellow.png", "res/button_grey.png"));

	lbOver = Label::createWithTTF("Game Over", FONT_NAME, 64.0f);
	overPanel->addChild(lbOver);
	lbOver->setColor(Color3B(0, 0, 0));
	lbOver->setPosition(Vec2(600 / 2, 300));

	btnHome->setPosition(Vec2(200, 100));
	btnQuit->setPosition(Vec2(400, 100));

	btnHome->setScale(1.3);
	btnQuit->setScale(1.3);

	btnHome->setTitleFontName(FONT_NAME);
	btnQuit->setTitleFontName(FONT_NAME);

	btnHome->setTitleColor(Color3B(255, 255, 255));
	btnQuit->setTitleColor(Color3B(255, 255, 255));

	btnHome->setTitleText("HOME");
	btnQuit->setTitleText("QUIT");

	btnHome->addClickEventListener([=](Ref* r) {
		auto scene = SceneHome::create();
		auto transit = TransitionSlideInL::create(0.125f, scene);
		Director::getInstance()->replaceScene(transit);
		//world->removeAllBodies();
	});

	btnQuit->addClickEventListener([=](Ref* r) {
		Director::getInstance()->end();
	});
}

Unit * SceneIngame::getPlayer()
{
	return this->player;
}

void SceneIngame::onKeyPressed(EventKeyboard::KeyCode c, Event * e)
{
	const bool value = true;
	switch (c) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW: up = value; break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: down = value; break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: left = value; break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: right = value; break;
	}
}

void SceneIngame::onKeyReleased(EventKeyboard::KeyCode c, Event * e)
{
	const bool value = false;
	switch (c) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW: up = value; break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: down = value; break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: left = value; break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: right = value; break;
	}
}

bool SceneIngame::onContactBegin(PhysicsContact & contact)
{
	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();
	Node* a = contact.getShapeA()->getBody()->getNode();
	Node* b = contact.getShapeB()->getBody()->getNode();

	if (a == nullptr) return true;
	if (b == nullptr) return true;

	if (tagA == TAG_ENEMY_BULLET && tagB == TAG_PLAYER) {
		//setScore(getScore());
		b->removeFromParent();
		player = nullptr;
		showOverPanel();
	}
	if (tagB == TAG_ENEMY_BULLET && tagA == TAG_PLAYER) {
		//setScore(getScore());
		a->removeFromParent();
		player = nullptr;
		showOverPanel();
	}

	return true;
}

void SceneIngame::set_level(int level)
{
	this->level = level;
}

void SceneIngame::logic(float dt)
{
	if (!player) return;

	Vec2 pos = player->getPosition();

	if (up) {
		pos += Vec2(0, dt*PLAYER_MOVEMENT_SPEED);
		if (pos.y >= 720){
			pos -= Vec2(0, dt*PLAYER_MOVEMENT_SPEED);
		}
	} 
	if (down) {
		pos -= Vec2(0, dt*PLAYER_MOVEMENT_SPEED);
		if (pos.y <= 0) {
			pos += Vec2(0, dt*PLAYER_MOVEMENT_SPEED);
		}
	}
	if (left) {
		pos -= Vec2(dt*PLAYER_MOVEMENT_SPEED, 0);
		if (pos.x <= 0) {
			pos += Vec2(dt*PLAYER_MOVEMENT_SPEED, 0);
		}
	}
	if (right) {
		pos += Vec2(dt*PLAYER_MOVEMENT_SPEED, 0);
		if (pos.x >= 1280) {
			pos -= Vec2(dt*PLAYER_MOVEMENT_SPEED, 0);
		}
	}

	player->setPosition(pos);
}


void SceneIngame::showOverPanel()
{
	overPanel->setVisible(true);

	auto pos = overPanel->getPosition();
	overPanel->setPosition(pos - Vec2(0, 1000));
	overPanel->runAction(EaseExponentialOut::create(MoveTo::create(0.125f, pos)));
}

void SceneIngame::hideOverPanel()
{
	auto pos = overPanel->getPosition();
	overPanel->runAction(Sequence::create(
		EaseExponentialOut::create(MoveTo::create(0.25f, pos - Vec2(0, 1000))),
		CallFunc::create([=]() {
		overPanel->setPosition(pos);
		overPanel->setVisible(false);
	}),
		nullptr
		));
}

void SceneIngame::setScore(long long score)
{
	sprintf(scoreString, "Score: %ld", score);
	lbScore->setString(scoreString);
}

long long SceneIngame::getScore()
{
	return score;
}
