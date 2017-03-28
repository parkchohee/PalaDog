#include "stdafx.h"
#include "levelUpScene.h"


levelUpScene::levelUpScene()
{
}


levelUpScene::~levelUpScene()
{
}

HRESULT levelUpScene::init()
{
	_bgImage = IMAGEMANAGER->findImage("levUpBG");
	_btnNext.image = IMAGEMANAGER->findImage("btnNext");
	_btnNext.rc = RectMakeCenter(860, 500, _btnNext.image->getFrameWidth(), _btnNext.image->getFrameHeight());
	_btnNext.frameX = 0;

	_touchImage[0].skiilLev = DATABASE->getElementData()->foodCountLev;
	_touchImage[1].skiilLev = DATABASE->getElementData()->foodLev;
	_touchImage[2].skiilLev = DATABASE->getElementData()->mpCountLev;
	_touchImage[3].skiilLev = DATABASE->getElementData()->mpLev;

	for (int i = 0; i < 4; i++)
	{
		_touchImage[i].rc = RectMake(35 + (i * 222), 140, 222, 250);
		_levUp[i].image = IMAGEMANAGER->findImage("levUpnum");
		_levUp[i].rc = RectMake(125 + (i * 222), 392, _levUp[i].image->getFrameWidth(), _levUp[i].image->getFrameHeight());
	}

	_sPointNum = DATABASE->getElementData()->skillPoint;

	return S_OK;
}

void levelUpScene::release()
{
}

void levelUpScene::update()
{
	levImage();
	levUp();
	btnNextTouch();
	setPointInfo();
}

void levelUpScene::render()
{
	_bgImage->render(getMemDC());
	draw();
}

void levelUpScene::draw()
{
	for (int i = 0; i < 4; i++)
	{
		_levUp[i].image->frameRender(getMemDC(), _levUp[i].rc.left, _levUp[i].rc.top, _levUp[i].frameX, 0);
	}

	_btnNext.image->frameRender(getMemDC(), _btnNext.rc.left, _btnNext.rc.top, _btnNext.frameX, 0);
}

void levelUpScene::levImage()
{
	char str[32];

	for (int i = 0; i < 4; i++)
	{
		_levUp[i].frameX = _touchImage[i].skiilLev + 2;
	}
}

void levelUpScene::levUp()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_touchImage[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_sPointNum != 0 && _touchImage[i].skiilLev < 5)
				{
					_touchImage[i].skiilLev += 1;
					_sPointNum -= 1;
				}
			}
		}
	}
}

void levelUpScene::btnNextTouch()
{
	if (PtInRect(&_btnNext.rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_btnNext.frameX = 1;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_btnNext.frameX = 0;

			DATABASE->setFoodCountLev(_touchImage[0].skiilLev);
			DATABASE->setFoodLev(_touchImage[1].skiilLev);
			DATABASE->setMpCountLev(_touchImage[2].skiilLev);
			DATABASE->setMpLev(_touchImage[3].skiilLev);

			DATABASE->setMaxMp(100 + DATABASE->getElementData()->mpLev * 10);
			DATABASE->setMaxFood(100 + DATABASE->getElementData()->foodLev * 10);
			DATABASE->setMpCount(30 - DATABASE->getElementData()->mpCountLev * 2);
			DATABASE->setFoodCount(30 - DATABASE->getElementData()->foodCountLev * 2);
			DATABASE->setSkillPoint(_sPointNum);

			DATABASE->saveDatabase();
			SCENEMANAGER->changeScene("stageSelectScene");
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			_btnNext.frameX = 0;
	}
}

void levelUpScene::setPointInfo()
{
	_foodIncreaseMax = _touchImage[0].skiilLev;
	_foodSpeedUp = _touchImage[1].skiilLev;
	_mpIncreaseMax = _touchImage[2].skiilLev;
	_mpSpeedUp = _touchImage[3].skiilLev;
}
