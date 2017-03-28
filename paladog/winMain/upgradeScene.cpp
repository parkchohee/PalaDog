#include "stdafx.h"
#include "upgradeScene.h"


upgradeScene::upgradeScene()
{
}


upgradeScene::~upgradeScene()
{
}

HRESULT upgradeScene::init()
{
	_bgImage = IMAGEMANAGER->findImage("upgradeUnit");
	_btnNext.image = IMAGEMANAGER->findImage("btnNext");
	_btnNext.rc = RectMakeCenter(860, 500, _btnNext.image->getFrameWidth(), _btnNext.image->getFrameHeight());
	_btnNext.frameX = 0;
	//유닛버튼 이미지
	for (int i = 0; i < SLOTMAX; i++)
	{
		_unitSlot[i].image = IMAGEMANAGER->findImage("slot_1m");
		sprintf_s(_unitSlot[i].imageName, "slot_%dm", i + 1);
		_unitSlot[i].state = UNSHOW;
		if (i < 3)
		{
			_unitSlot[i].x = 25 + (i * 110);
			_unitSlot[i].y = 96;
		}
		if (i > 2 && i < 6)
		{
			_unitSlot[i].x = 25 + ((i - 3) * 110);
			_unitSlot[i].y = 216;
		}
		if (i > 5)
		{
			_unitSlot[i].x = 25 + ((i - 6) * 110);
			_unitSlot[i].y = 336;
		}
		_unitSlot[i].rc = RectMake(_unitSlot[i].x, _unitSlot[i].y, _unitSlot[i].image->getFrameWidth(), _unitSlot[i].image->getFrameHeight());
	}

	//금 이미지
	for (int i = 0; i < 8; i++)
	{
		_goldImage_w[i].image = IMAGEMANAGER->findImage("goldNum_w");
		_goldImage_w[i].frameX = 0;
		_goldImage_w[i].x = 120 + (i * 28);
		_goldImage_w[i].y = 495;
		_goldImage_w[i].rc = RectMakeCenter(_goldImage_w[i].x, _goldImage_w[i].y, 28, 32);
	}

	//showImage
	_showImage.showImage = NULL;
	_showImage.showImageName = NULL;
	sprintf_s(_showImage.imageName, "0");
	_showImage.x = 550;
	_showImage.y = 250;
	_showImage.rc = RectMakeCenter(_showImage.x, _showImage.y, 150, 150);
	_showImage.nameRc = RectMakeCenter(550, 130, 300, 50);

	//upgradeImage
	for (int i = 0; i < 10; i++)
	{
		_upImage[i].attackUp = NULL;
		_upImage[i].hpUp = NULL;
		_upImage[i].goldUp = NULL;
		_upImage[i].aRc = RectMakeCenter(700 + (i * 22), 145, 22, 24);
		_upImage[i].hRc = RectMakeCenter(700 + (i * 22), 210, 22, 24);
		_upImage[i].gRc = RectMakeCenter(650 + (i * 28), 240, 28, 32);
	}

	//upgradeProgressBar
	_hpBar = new progressBar;
	_attackBar = new progressBar;
	_speedBar = new progressBar;
	_delayBar = new progressBar;

	_hpBar->init(450, 454, 250, 5);
	_attackBar->init(450, 474, 250, 5);
	_speedBar->init(450, 494, 250, 5);
	_delayBar->init(450, 514, 280, 5);

	_hpBar->setGauge(0, 1000);
	_attackBar->setGauge(0, 500);
	_speedBar->setGauge(0, 10);
	_delayBar->setGauge(0, 100);

	//upgradeBtn
	_btnUpgrade.image = IMAGEMANAGER->findImage("btnUnUpgrade");
	_btnUpgrade.rc = RectMakeCenter(820, 295, 195, 75);
	_btnUpgrade.frameX = 0;
	_btnUpgrade.isUse = false;

	//LevelImage
	for (int i = 0; i < 4; i++)
	{
		_levImage[i].firstImage = IMAGEMANAGER->findImage("upUnitNum");
		_levImage[i].secondImage = IMAGEMANAGER->findImage("upUnitNum");;
		_levImage[i].firstFrame = 0;
		_levImage[i].secondFrameX = 0;
		for (int j = 0; j < 2; j++)
		{
			_levImage[i].rc[j] = RectMakeCenter((_unitSlot[i].x + 15) + (j * 22), _unitSlot[i].y + 98, 22, 25);
		}
	}

	//프레임 움직임 변수
	_frameX = 0;
	_count = 0;
	_selectSlotNum = 4;

	_gold = DATABASE->getElementData()->gold;
	unitStateInfo();
	unitUpgeadeInfo();
	return S_OK;
}

void upgradeScene::release()
{
}

void upgradeScene::update()
{
	keyControl();
	unitUpgeadeInfo();
	setSlotFrame();
	levImage();
	btnNextTouch();
	if (_selectSlotNum != 4)
	{
		showUpgradeImage(_selectSlotNum);
		upgradeUse();
	}
	if (_showImage.showImage != NULL)   frameCount();
	upgradeClick();
	_hpBar->update();
	_attackBar->update();
	_speedBar->update();
	_delayBar->update();
}

void upgradeScene::render()
{
	_bgImage->render(getMemDC());
	_hpBar->render();
	_attackBar->render();
	_speedBar->render();
	_delayBar->render();
	showImage();
	goldRender();
	goldImage();
	for (int i = 0; i < SLOTMAX; i++)
	{
		if (i < 4)
		{
			_unitSlot[i].image = IMAGEMANAGER->findImage(_unitSlot[i].imageName);
			_unitSlot[i].image->frameRender(getMemDC(), _unitSlot[i].rc.left, _unitSlot[i].rc.top, _unitSlot[i].state, 0);
		}
		else
		{
			_unitSlot[i].image = IMAGEMANAGER->findImage("slot_lock");
			_unitSlot[i].image->frameRender(getMemDC(), _unitSlot[i].rc.left, _unitSlot[i].rc.top);
		}
	}
}

void upgradeScene::keyControl()
{
	for (int i = 0; i < SLOTMAX - 5; i++)
	{
		if (PtInRect(&_unitSlot[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_selectSlotNum = i;
				switch (i)
				{
				case 0:
					_showImage.showImage = IMAGEMANAGER->findImage("MouseMove");
					_showImage.showImageName = IMAGEMANAGER->findImage("mName");
					_showImage.x = 560;
					_showImage.y = 270;
					break;
				case 1:
					_showImage.showImage = IMAGEMANAGER->findImage("RabbitMove");
					_showImage.showImageName = IMAGEMANAGER->findImage("rName");
					_showImage.x = 550;
					_showImage.y = 250;
					break;
				case 2:
					_showImage.showImage = IMAGEMANAGER->findImage("BearMove");
					_showImage.showImageName = IMAGEMANAGER->findImage("bName");
					_showImage.x = 550;
					_showImage.y = 250;
					break;
				case 3:
					_showImage.showImage = IMAGEMANAGER->findImage("KangarooMove");
					_showImage.showImageName = IMAGEMANAGER->findImage("kName");
					_showImage.x = 550;
					_showImage.y = 250;
					break;
				}
			}
		}
	}
}

void upgradeScene::showImage()
{
	if (_showImage.showImage != NULL)
	{
		_showImage.showImage->frameRender(getMemDC(), _showImage.rc.left, _showImage.rc.top, _frameX, 0);
		_showImage.showImageName->render(getMemDC(), _showImage.nameRc.left, _showImage.nameRc.top);
	}
	for (int i = 0; i < 10; i++)
	{
		if (_upImage[i].attackUp != NULL)
			_upImage[i].attackUp->frameRender(getMemDC(), _upImage[i].aRc.left, _upImage[i].aRc.top, _upImage[i].aFrameX, 0);
		if (_upImage[i].hpUp != NULL)
			_upImage[i].hpUp->frameRender(getMemDC(), _upImage[i].hRc.left, _upImage[i].hRc.top, _upImage[i].hFrameX, 0);
		if (_upImage[i].goldUp != NULL)
			_upImage[i].goldUp->frameRender(getMemDC(), _upImage[i].gRc.left, _upImage[i].gRc.top, _upImage[i].gFrameX, 0);
		if (_btnUpgrade.image != NULL)
			_btnUpgrade.image->frameRender(getMemDC(), _btnUpgrade.rc.left, _btnUpgrade.rc.top, _btnUpgrade.frameX, 0);
		for (int i = 0; i < 4; i++)
		{
			if (_levImage[i].firstImage != NULL)
				_levImage[i].firstImage->frameRender(getMemDC(), _levImage[i].rc[0].left, _levImage[i].rc[0].top, _levImage[i].firstFrame, 0);
			_levImage[i].secondImage->frameRender(getMemDC(), _levImage[i].rc[1].left, _levImage[i].rc[1].top, _levImage[i].secondFrameX, 0);
		}
		_btnNext.image->frameRender(getMemDC(), _btnNext.rc.left, _btnNext.rc.top, _btnNext.frameX, 0);
	
	}
}

void upgradeScene::frameCount()
{
	_showImage.rc = RectMakeCenter(_showImage.x, _showImage.y, 150, 150);
	_showImage.nameRc = RectMakeCenter(550, 130, _showImage.showImageName->getWidth(), _showImage.showImageName->getHeight());
	_count++;

	if (_count % 10 == 0)
	{
		_frameX++;
		if (_frameX > _showImage.showImage->getMaxFrameX())
		{
			_frameX = 0;
			_count = 0;
		}
	}
}

void upgradeScene::goldImage()
{
	char str[32];
	int size;
	int num;
	sprintf_s(str, "%d", _gold);				
	size = strlen(str);

	for (int i = 0; i < 7 - size; i++)
	{
		_goldImage_w[i].image = NULL;
	}
	for (int i = 0; i <= size; i++)
	{
		_goldImage_w[7 - i].image = IMAGEMANAGER->findImage("goldNum_w");
		_goldImage_w[7 - i].frameX = ((int)str[size - i - 1]) - 46;
	}
}

void upgradeScene::goldRender()
{
	for (int i = 0; i < 8; i++)
	{
		if (_goldImage_w[i].image != NULL)
			_goldImage_w[i].image->frameRender(getMemDC(), _goldImage_w[i].rc.left, _goldImage_w[i].rc.top, _goldImage_w[i].frameX, 0);
	}
}


void upgradeScene::unitStateInfo()
{
	//쥐 유닛
	_unitSlot[0].unitState.attack = DATABASE->getElementData()->mouseAttack;
	_unitSlot[0].unitState.delay = DATABASE->getElementData()->mouseDelay;
	_unitSlot[0].unitState.hp = DATABASE->getElementData()->mouseHp;
	_unitSlot[0].unitState.lev = DATABASE->getElementData()->mouseLev;
	_unitSlot[0].unitState.speed = DATABASE->getElementData()->mouseSpeed;

	//토끼 유닛
	_unitSlot[1].unitState.attack = DATABASE->getElementData()->rabbitAttack;
	_unitSlot[1].unitState.delay = DATABASE->getElementData()->rabbitDelay;
	_unitSlot[1].unitState.hp = DATABASE->getElementData()->rabbitHp;
	_unitSlot[1].unitState.lev = DATABASE->getElementData()->rabbitLev;
	_unitSlot[1].unitState.speed = DATABASE->getElementData()->rabbitSpeed;

	//곰 유닛
	_unitSlot[2].unitState.attack = DATABASE->getElementData()->bearAttack;
	_unitSlot[2].unitState.delay = DATABASE->getElementData()->bearDelay;
	_unitSlot[2].unitState.hp = DATABASE->getElementData()->bearHp;
	_unitSlot[2].unitState.lev = DATABASE->getElementData()->bearLev;
	_unitSlot[2].unitState.speed = DATABASE->getElementData()->bearSpeed;

	//캥거루 유닛
	_unitSlot[3].unitState.attack = DATABASE->getElementData()->kangarooAttack;
	_unitSlot[3].unitState.delay = DATABASE->getElementData()->kangarooDelay;
	_unitSlot[3].unitState.hp = DATABASE->getElementData()->kangarooHp;
	_unitSlot[3].unitState.lev = DATABASE->getElementData()->kangarooLev;
	_unitSlot[3].unitState.speed = DATABASE->getElementData()->kangarooSpeed;
}

void upgradeScene::unitUpgeadeInfo()
{
	//쥐 업그레이드 정보
	_unitSlot[0].unitState.upgradeAttack = DATABASE->getElementData()->mouseUpgradeAttack;
	_unitSlot[0].unitState.upgradeHp = DATABASE->getElementData()->mouseUpgradeHp;
	_unitSlot[0].unitState.upgradeGold = DATABASE->getElementData()->mouseUpgradeGold * _unitSlot[0].unitState.lev;

	//토끼 업그레이드 정보
	_unitSlot[1].unitState.upgradeAttack = DATABASE->getElementData()->rabbitUpgradeAttack;
	_unitSlot[1].unitState.upgradeHp = DATABASE->getElementData()->rabbitUpgradeHp;
	_unitSlot[1].unitState.upgradeGold = DATABASE->getElementData()->rabbitUpgradeGold * _unitSlot[1].unitState.lev;

	//곰 업그레이드 정보
	_unitSlot[2].unitState.upgradeAttack = DATABASE->getElementData()->bearUpgradeAttack;
	_unitSlot[2].unitState.upgradeHp = DATABASE->getElementData()->bearUpgradeHp;
	if (_unitSlot[2].unitState.lev <= 1)
		_unitSlot[2].unitState.upgradeGold = 20000;
	else
		_unitSlot[2].unitState.upgradeGold = DATABASE->getElementData()->bearUpgradeGold * _unitSlot[2].unitState.lev;

	//캥거루 업그레이드 정보
	_unitSlot[3].unitState.upgradeAttack = DATABASE->getElementData()->kangarooUpgradeAttack;
	_unitSlot[3].unitState.upgradeHp = DATABASE->getElementData()->kangarooUpgradeHp;
	if (_unitSlot[3].unitState.lev <= 1)
		_unitSlot[3].unitState.upgradeGold = 40000;
	else
		_unitSlot[3].unitState.upgradeGold = DATABASE->getElementData()->kangarooUpgradeGold * _unitSlot[3].unitState.lev;
}

void upgradeScene::showUpgradeImage(int unitNum)
{
	char atkNum[32];
	char hpNum[32];
	char goldNum[32];
	int size = 0;
	sprintf_s(atkNum, "%d", _unitSlot[unitNum].unitState.upgradeAttack);
	sprintf_s(hpNum, "%d", _unitSlot[unitNum].unitState.upgradeHp);
	sprintf_s(goldNum, "%d", _unitSlot[unitNum].unitState.upgradeGold);

	size = strlen(atkNum);
	for (int i = 0; i < 9 - size; i++)
	{
		_upImage[i].attackUp = NULL;
	}
	for (int i = 0; i <= size; i++)
	{
		_upImage[9 - i].attackUp = IMAGEMANAGER->findImage("upUnitNum");
		if (i == size)   _upImage[9 - i].aFrameX = 0;
		else
		{
			_upImage[9 - i].aFrameX = (int)(atkNum[size - i - 1]) - 46;
		}
	}

	size = strlen(hpNum);
	for (int i = 0; i < 9 - size; i++)
	{
		_upImage[i].hpUp = NULL;
	}
	for (int i = 0; i <= size; i++)
	{
		_upImage[9 - i].hpUp = IMAGEMANAGER->findImage("upUnitNum");
		if (i == size)   _upImage[9 - i].hFrameX = 0;
		else
		{
			_upImage[9 - i].hFrameX = (int)(hpNum[size - i - 1]) - 46;
		}
	}

	size = strlen(goldNum);
	for (int i = 0; i < 9 - size; i++)
	{
		_upImage[i].goldUp = NULL;
	}
	for (int i = 0; i <= size; i++)
	{
		_upImage[9 - i].goldUp = IMAGEMANAGER->findImage("goldNum");
		if (i == size)   _upImage[9 - i].gFrameX = 0;
		else
		{
			_upImage[9 - i].gFrameX = (int)(goldNum[size - i - 1]) - 46;
		}
	}

	_hpBar->setGauge(_unitSlot[unitNum].unitState.hp, 1000);
	_attackBar->setGauge(_unitSlot[unitNum].unitState.attack, 500);
	_speedBar->setGauge(_unitSlot[unitNum].unitState.speed, 10);
	_delayBar->setGauge(_unitSlot[unitNum].unitState.delay, 100);

}

void upgradeScene::upgradeUse()
{
	if (_gold >= _unitSlot[_selectSlotNum].unitState.upgradeGold)
	{
		_btnUpgrade.isUse = true;
		_btnUpgrade.frameX = 1;
	}
	else if (_gold < _unitSlot[_selectSlotNum].unitState.upgradeGold)
	{
		_btnUpgrade.isUse = false;
		_btnUpgrade.frameX = 0;
	}
}

void upgradeScene::upgradeClick()
{
	if (PtInRect(&_btnUpgrade.rc, _ptMouse) && _btnUpgrade.isUse)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_btnUpgrade.frameX = 2;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_btnUpgrade.frameX = 1;
			unitLevUp();
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _btnUpgrade.isUse)
		{
			_btnUpgrade.frameX = 1;
		}
	}
}

void upgradeScene::unitLevUp()
{
	switch (_selectSlotNum)
	{
	case 0:
		DATABASE->setGold(DATABASE->getElementData()->gold - DATABASE->getElementData()->mouseUpgradeGold * DATABASE->getElementData()->mouseLev);
		DATABASE->setMouseLev(DATABASE->getElementData()->mouseLev + 1);
		DATABASE->setMouseHp(DATABASE->getElementData()->mouseHp + DATABASE->getElementData()->mouseUpgradeHp);
		DATABASE->setMouseAttack(DATABASE->getElementData()->mouseAttack + DATABASE->getElementData()->mouseUpgradeAttack);
		break;
	case 1:
		DATABASE->setGold(DATABASE->getElementData()->gold - DATABASE->getElementData()->rabbitUpgradeGold * DATABASE->getElementData()->rabbitLev);
		DATABASE->setRabbitLev(DATABASE->getElementData()->rabbitLev + 1);
		DATABASE->setRabbitHp(DATABASE->getElementData()->rabbitHp + DATABASE->getElementData()->rabbitUpgradeHp);
		DATABASE->setRabbitAttack(DATABASE->getElementData()->rabbitAttack + DATABASE->getElementData()->rabbitUpgradeAttack);
		break;
	case 2:
		DATABASE->setGold(DATABASE->getElementData()->gold - DATABASE->getElementData()->bearUpgradeGold * DATABASE->getElementData()->bearLev);
		DATABASE->setBearLev(DATABASE->getElementData()->bearLev + 1);
		DATABASE->setBearHp(DATABASE->getElementData()->bearHp + DATABASE->getElementData()->bearUpgradeHp);
		DATABASE->setBearAttack(DATABASE->getElementData()->bearAttack + DATABASE->getElementData()->bearUpgradeAttack);
		break;
	case 3:
		DATABASE->setGold(DATABASE->getElementData()->gold - DATABASE->getElementData()->kangarooUpgradeGold * DATABASE->getElementData()->kangarooLev);
		DATABASE->setKangarooLev(DATABASE->getElementData()->kangarooLev + 1);
		DATABASE->setKangarooHp(DATABASE->getElementData()->kangarooHp + DATABASE->getElementData()->kangarooUpgradeHp);
		DATABASE->setKangarooAttack(DATABASE->getElementData()->kangarooAttack + DATABASE->getElementData()->kangarooUpgradeAttack);

		break;
	}

	// 변경된 값으로 셋팅
	unitStateInfo();
	unitUpgeadeInfo();
	
	// 돈 업데이트
	_gold = DATABASE->getElementData()->gold;

	// 데이터베이스 저장
	DATABASE->saveDatabase();
	
	
	//_gold -= _unitSlot[_selectSlotNum].unitState.upgradeGold;
	//_unitSlot[_selectSlotNum].unitState.lev += 1;
	//_unitSlot[_selectSlotNum].unitState.hp += _unitSlot[_selectSlotNum].unitState.upgradeHp;
	//_unitSlot[_selectSlotNum].unitState.attack += _unitSlot[_selectSlotNum].unitState.upgradeAttack;
}

void upgradeScene::setSlotFrame()
{
	for (int i = 0; i < 4; i++)
	{
		if (_unitSlot[i].unitState.lev != 0)
		{
			_unitSlot[i].state = SHOW;
		}
	}
}

void upgradeScene::levImage()
{
	char str[32];
	int size;
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(str, "%d", _unitSlot[i].unitState.lev);
		size = strlen(str);

		if (size < 2)
		{
			_levImage[i].firstImage = NULL;
			_levImage[i].secondImage = IMAGEMANAGER->findImage("upUnitNum");
			_levImage[i].secondFrameX = (int)(str[0]) - 46;
		}
		else
		{
			_levImage[i].firstImage = IMAGEMANAGER->findImage("upUnitNum");
			_levImage[i].firstFrame = (int)(str[0]) - 46;
			_levImage[i].secondImage = IMAGEMANAGER->findImage("upUnitNum");
			_levImage[i].secondFrameX = (int)(str[1]) - 46;
		}
	}
}

void upgradeScene::btnNextTouch()
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
			SCENEMANAGER->changeScene("levelUpScene");
		}
	}
	else
	{
		//if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && !PtInRect(&_btnUpgrade.rc, _ptMouse))	_btnNext.frameX = 0;
	}
}
