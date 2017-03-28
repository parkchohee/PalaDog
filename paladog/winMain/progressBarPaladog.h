#pragma once

#include "gameNode.h"

class progressBarPaladog : public gameNode
{
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarForward;
	image* _progressBarBack;

public:
	progressBarPaladog();
	~progressBarPaladog();
	
	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	//체력바 게이지
	void setGauge(float currentGauge, float maxGauge);

	//좌표 셋업
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
};

