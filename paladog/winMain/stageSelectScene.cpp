#include "stdafx.h"
#include "stageSelectScene.h"


stageSelectScene::stageSelectScene()
{
}


stageSelectScene::~stageSelectScene()
{
}

HRESULT stageSelectScene::init()
{
	_bgImage = IMAGEMANAGER->findImage("selectStage");
	_btnUpgrade.image = IMAGEMANAGER->findImage("btnUpgrade");

	for (int i = 0; i < STAGEMAX; i++)
	{
		_stage[i].stageNum = IMAGEMANAGER->findImage("stageLock");
		_stage[i].stageStroke = IMAGEMANAGER->findImage("stageStroke");
		_stage[i].stageStar = IMAGEMANAGER->findImage("stageStar");
		sprintf_s(_stage[i].imageName, "stage%d", i + 1);

		if (i < 4)
		{
			_stage[i].x = 215 + (i * 170);
			_stage[i].y = 200;
		}
		else if (i > 3 && i < 8)
		{
			_stage[i].x = 215 + ((i - 4) * 170);
			_stage[i].y = 280;
		}
		else
		{
			_stage[i].x = 215 + ((i - 8) * 170);
			_stage[i].y = 360;
		}

		_stage[i].rc = RectMakeCenter(_stage[i].x, _stage[i].y, _stage[i].stageNum->getWidth(), _stage[i].stageNum->getHeight());
		_stage[i].strokeRc = RectMakeCenter(_stage[i].x, _stage[i].y, _stage[i].stageStroke->getWidth(), _stage[i].stageStroke->getHeight());
		_stage[i].useStar = 2;
		_stage[i]._isCheck = false;

	}

	_btnUpgrade.checkFrame = 0;
	_btnUpgrade.rc = RectMake(0, WINSIZEY - _btnUpgrade.image->getFrameHeight(), _btnUpgrade.image->getFrameWidth(), _btnUpgrade.image->getFrameHeight());

	// 데이터베이스 셋팅
	for (int i = 0; i < STAGEMAX; i++)
	{
		if (i < DATABASE->getElementData()->currentStage)
			_stage[i]._isOpen = true;
		else
			_stage[i]._isOpen = false;
	}

	_stage[0].useStar = DATABASE->getElementData()->stage1;
	_stage[1].useStar = DATABASE->getElementData()->stage2;
	_stage[2].useStar = DATABASE->getElementData()->stage3;
	_stage[3].useStar = DATABASE->getElementData()->stage4;
	_stage[4].useStar = DATABASE->getElementData()->stage5;
	_stage[5].useStar = DATABASE->getElementData()->stage6;
	_stage[6].useStar = DATABASE->getElementData()->stage7;
	_stage[7].useStar = DATABASE->getElementData()->stage8;
	_stage[8].useStar = DATABASE->getElementData()->stage9;
	_stage[9].useStar = DATABASE->getElementData()->stage10;
	_stage[10].useStar = DATABASE->getElementData()->stage11;
	_stage[11].useStar = DATABASE->getElementData()->stage12;

	return S_OK;
}

void stageSelectScene::release()
{
}

void stageSelectScene::update()
{
	imageLoad();
	keyControl();
}

void stageSelectScene::render()
{
	_bgImage->render(getMemDC()); //배경

	for (int i = 0; i < STAGEMAX; i++)
	{
		_stage[i].stageNum->render(getMemDC(), _stage[i].rc.left, _stage[i].rc.top);
		
		if (_stage[i]._isCheck)	
			_stage[i].stageStroke->render(getMemDC(), _stage[i].strokeRc.left, _stage[i].strokeRc.top);

		if (_stage[i]._isOpen && _stage[i].useStar != 0)
			_stage[i].stageStar->frameRender(getMemDC(), _stage[i].rc.left + 75, _stage[i].rc.top + 5, _stage[i].useStar, 0);

	}

	_btnUpgrade.image->frameRender(getMemDC(), _btnUpgrade.rc.left, _btnUpgrade.rc.top, _btnUpgrade.checkFrame, 0);
	
}

void stageSelectScene::imageLoad()
{
	for (int i = 0; i < STAGEMAX; i++)
	{
		if (_stage[i]._isOpen)	_stage[i].stageNum = IMAGEMANAGER->findImage(_stage[i].imageName);
		else	_stage[i].stageNum = IMAGEMANAGER->findImage("stageLock");
	}
}

void stageSelectScene::keyControl()
{
	for (int i = 0; i < STAGEMAX; i++)
	{
		if (PtInRect(&_stage[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_stage[i]._isOpen)
				{
					DATABASE->setNowPlayStage(i);
					DATABASE->saveDatabase();

					if (i % 3 == 2)
					{
						SCENEMANAGER->changeScene("threeStageScene");
					}
					else
					{
						SCENEMANAGER->changeScene("playScene");
					}
				}
				
			
				//_stage[i]._isOpen = !_stage[i]._isOpen;
				//_stage[i]._isCheck = true;
				
			}

		/*	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				_stage[i]._isCheck = false;
			}*/
		}
	/*	else
		{
			_stage[i]._isCheck = false;
		}*/
	}
	btnUpClick();
}

void stageSelectScene::btnUpClick()
{
	if (PtInRect(&_btnUpgrade.rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_btnUpgrade.checkFrame = 1;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_btnUpgrade.checkFrame = 0;
			SCENEMANAGER->changeScene("upgradeScene");
		}
	}
	else
	{
		_btnUpgrade.checkFrame = 0;
	}
}
