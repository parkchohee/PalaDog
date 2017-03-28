#include "stdafx.h"
#include "DieScene.h"


DieScene::DieScene()
{
}


DieScene::~DieScene()
{
}

HRESULT DieScene::init()
{
	DieMap = IMAGEMANAGER->findImage("DieScene");
	_rc = RectMake(640, 410, 202, 96);
	FrameX = 0;
	NextFrameX = 0;
	Count = 0;

	ShowNext = false;

	return S_OK;
}

void DieScene::release()
{

}

void DieScene::update()
{
	DieCount();
	btnNext();
}

void DieScene::render()
{
	DieMap->frameRender(getMemDC(), 0, 0, FrameX, 0);

	if (ShowNext == true)
	{
		IMAGEMANAGER->findImage("Next")->frameRender(getMemDC(), _rc.left, _rc.top, NextFrameX, 0);
	}
}

void DieScene::btnNext()
{

	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			NextFrameX = 1;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			NextFrameX = 0;
			SCENEMANAGER->changeScene("stageSelectScene");
		}
	}
}

void DieScene::DieCount()
{
	Count++;

	if (Count % 7 == 0)
	{
		FrameX++;

		if (FrameX > DieMap->getMaxFrameX())
		{
			FrameX = DieMap->getMaxFrameX();
			Count = 0;
			ShowNext = true;
		}
	}
}
