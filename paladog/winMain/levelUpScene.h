#pragma once
#include "gameNode.h"

struct tagTouch
{
	RECT rc;
	int skiilLev;
};

struct tagLev
{
	image* image;
	RECT rc;
	int frameX;
};

class levelUpScene : public gameNode
{
private:
	image* _bgImage;
	tagTouch _touchImage[4]; // 식량속도, 최대값, 마나속도, 최대값
	tagLev _levUp[4];
	tagLev _btnNext;

	int _sPointNum;
	int _foodIncreaseMax;
	int _foodSpeedUp;
	int _mpIncreaseMax;
	int _mpSpeedUp;
public:
	levelUpScene();
	~levelUpScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void draw();
	void levImage();
	void levUp();
	void btnNextTouch();
	void setPointInfo();
};

