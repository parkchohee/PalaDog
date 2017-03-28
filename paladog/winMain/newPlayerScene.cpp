#include "stdafx.h"
#include "newPlayerScene.h"


newPlayerScene::newPlayerScene()
{
}


newPlayerScene::~newPlayerScene()
{
}

HRESULT newPlayerScene::init()
{
	_rc = RectMake(780, 0, 180, 70);
	_count = 0;
	_select = false;
	return S_OK;
}

void newPlayerScene::release()
{
}

void newPlayerScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if(PtInRect(&_rc, _ptMouse))
			_select = true;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse) && _select == true)
		{
			_count++;

			if(_count > 5)
				SCENEMANAGER->changeScene("stageSelectScene");
		}
		else
			_select = false;
	}
}

void newPlayerScene::render()
{
	switch (_count)
	{
	case 0:
		IMAGEMANAGER->render("newPlayer01", getMemDC());
		break;
	case 1:
		IMAGEMANAGER->render("newPlayer02", getMemDC());
		break;
	case 2:
		IMAGEMANAGER->render("newPlayer03", getMemDC());
		break;
	case 3:
		IMAGEMANAGER->render("newPlayer04", getMemDC());
		break;
	case 4:
		IMAGEMANAGER->render("newPlayer05", getMemDC());
		break;
	case 5:
		IMAGEMANAGER->render("newPlayer06", getMemDC());
		break;
	}

	IMAGEMANAGER->render("newPlayerNextBtn", getMemDC(), _rc.left, _rc.top);

}
