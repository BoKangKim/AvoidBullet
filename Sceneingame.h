#pragma once
#include "stdafx.h"
#include "Unit.h"

class SceneIngame : public Scene {
private:
	Unit* player = nullptr;
	bool up = false, down = false, left = false, right = false;
	int level = 1;
	long long score;
	char scoreString[128];
public:
	Scale9Sprite* overPanel;
	Label* lbScore;
	Label* lbOver;
	Button* btnHome;
	Button* btnQuit;
	Button* btnRetry;

	static SceneIngame* create(int level);
	virtual bool init(int level);
	virtual void onEnter() override;
	void initUI();

	Unit* getPlayer();

	void onKeyPressed(EventKeyboard::KeyCode c, Event* e);
	void onKeyReleased(EventKeyboard::KeyCode c, Event* e);
	bool onContactBegin(PhysicsContact& contact);
	void set_level(int level);

	void logic(float dt);

	void showOverPanel();
	void hideOverPanel();

	void setScore(long long score);
	long long getScore();
};