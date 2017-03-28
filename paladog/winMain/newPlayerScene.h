#pragma once

#include "gameNode.h"

class newPlayerScene : public gameNode
{
	RECT _rc;

	int _count;
	bool _select;

public:
	newPlayerScene();
	~newPlayerScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

