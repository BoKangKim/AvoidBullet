#ifndef __SCENE_HOME_H__
#define __SCENE_HOME_H__

#include "stdafx.h"

class SceneHome : public Scene
{
public:
	Button* btnEasy;
	Button* btnNormal;
	Button* btnDifficult;
	Button* btnQuit;

	static SceneHome* create();
	virtual bool init() override;
	virtual void onEnter() override;
};

#endif // !__SCENE_HOME_H__