#pragma once

#include "gameNode.h"
#define STAGEMAX 12

struct tagStage
{
	image* stageNum;
	image* stageStroke;
	image* stageStar;
	RECT rc;
	RECT strokeRc;
	int x, y;
	bool _isOpen;
	bool _isCheck;
	int useStar;
	char imageName[32];
};

struct tagUpgrade
{
	image* image;
	RECT rc;
	int checkFrame;
};

class stageSelectScene : public gameNode
{
private:
	tagStage _stage[STAGEMAX];
	tagUpgrade _btnUpgrade;
	image* _bgImage;
public:
	stageSelectScene();
	~stageSelectScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageLoad();
	void keyControl();
	void btnUpClick();
};

