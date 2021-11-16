#include "stdafx.h"
#include "SceneHome.h"
#include "Sceneingame.h"

SceneHome * SceneHome::create()
{
	auto ret = new SceneHome();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool SceneHome::init()
{
	if (!Scene::init()) return false;

	Sprite* img = Sprite::create("res/titleImg.png");
	addChild(img);
	img->setPosition(Vec2(1280/2, 720/2));

	addChild(btnEasy = Button::create("res/button_blue.png", "res/button_yellow.png", "res/button_grey.png"));
	addChild(btnNormal = Button::create("res/button_blue.png", "res/button_yellow.png", "res/button_grey.png"));
	addChild(btnDifficult = Button::create("res/button_blue.png", "res/button_yellow.png", "res/button_grey.png"));
	addChild(btnQuit = Button::create("res/button_blue.png", "res/button_yellow.png", "res/button_grey.png"));

	btnEasy->setPosition(Vec2(1280/2, 290));
	btnNormal->setPosition(Vec2(1280 / 2, 210));
	btnDifficult->setPosition(Vec2(1280 / 2, 130));
	btnQuit->setPosition(Vec2(1280 / 2, 50));

	btnEasy->setScale(1.5);
	btnNormal->setScale(1.5);
	btnDifficult->setScale(1.5);
	btnQuit->setScale(1.5);

	btnEasy->setTitleFontName(FONT_NAME);
	btnNormal->setTitleFontName(FONT_NAME);
	btnDifficult->setTitleFontName(FONT_NAME);
	btnQuit->setTitleFontName(FONT_NAME);

	btnEasy->setTitleColor(Color3B(255,255,255));
	btnNormal->setTitleColor(Color3B(255, 255, 255));
	btnDifficult->setTitleColor(Color3B(255, 255, 255));
	btnQuit->setTitleColor(Color3B(255, 255, 255));

	btnEasy->setTitleText("EASY");
	btnNormal->setTitleText("NORMAL");
	btnDifficult->setTitleText("DIFFICULT");
	btnQuit->setTitleText("QUIT");

	btnEasy->addClickEventListener([=](Ref* r) {
		auto scene = SceneIngame::create(0);
		auto transit = TransitionSlideInR::create(0.125f,scene);
		Director::getInstance()->replaceScene(transit);
	});
	btnNormal->addClickEventListener([=](Ref* r) {
		auto scene = SceneIngame::create(1);
		auto transit = TransitionSlideInR::create(0.125f, scene);
		Director::getInstance()->replaceScene(transit);
	});
	btnDifficult->addClickEventListener([=](Ref* r) {
		auto scene = SceneIngame::create(2);
		auto transit = TransitionSlideInR::create(0.125f, scene);
		Director::getInstance()->replaceScene(transit);
	});
	btnQuit->addClickEventListener([=](Ref* r) {
		Director::getInstance()->end();
	});

	return true;
}
