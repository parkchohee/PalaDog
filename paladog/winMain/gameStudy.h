#pragma once

#include "gameNode.h"
#include "startScene.h"
#include "stageSelectScene.h"
#include "playScene.h"
#include "newPlayerScene.h"
#include "upgradeScene.h"
#include "levelUpScene.h"
#include "threeStageScene.h"
#include "DieScene.h"


class gameStudy : public gameNode
{
private:

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

