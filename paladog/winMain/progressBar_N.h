#pragma once
#include "gameNode.h"

class progressBar_N : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarForward;
	image* _progressBarBack;

	string fImage;
	string sImage;

public:
	progressBar_N();
	~progressBar_N();

	HRESULT init(int x, int y, int width, int height, string fImageName, string sImageName);
	void release();
	void update();
	void render();

	//ü�¹� ������
	void setGauge(float currentGauge, float maxGauge);

	//��ǥ �¾�
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
};

