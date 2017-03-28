#pragma once
#include "gameNode.h"
#include "paladog.h"




class DieScene :public gameNode
	
{
	image * DieMap;
	RECT _rc;

	int FrameX;
	int NextFrameX;
	int Count;
	
	bool ShowNext;

public:
	DieScene();
	~DieScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void btnNext();
	void DieCount();


};

