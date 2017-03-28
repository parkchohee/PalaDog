#include "stdafx.h"
#include "threeStageScene.h"


threeStageScene::threeStageScene()
{
}


threeStageScene::~threeStageScene()
{
}

HRESULT threeStageScene::init()
{
	_cRc = RectMakeCenter(730, 300, 5, 500);
	_soldier = new soldierManager;
	_soldier->init(_cRc);

	_paladog = new paladog;
	_paladog->init();

	_soldier->setPaladogMemoryLink(_paladog);

	_offsetX = 0;
	_count = 0;
	_bonusGold = 0;
	//일시정지용
	_psPause = RectMake(890, 5, 62, 56);
	_isPause = false;

	_deathGauge = new progressBar_N;
	_deathGauge->init(364, 22, 215, 10, "hpBarBottom3", "hpBarBottom4");
	_deathGauge->setGauge(_soldier->getDeathCount(), MAXMONSTER);

	//stageClear
	_isClear = false;
	_useStar = 0;
	_stageClear.window = IMAGEMANAGER->findImage("clearWindow");
	_stageClear.rc = RectMakeCenter(CENTERX, CENTERY, _stageClear.window->getWidth(), _stageClear.window->getHeight());
	_stageClear.btn = IMAGEMANAGER->findImage("btnNext");
	_stageClear.bRc = RectMakeCenter(0, 0, 0, 0);
	
	for (int i = 0; i < 3; i++)
	{
		if (i < 2)
		{
			_stageClear.stageNum[i] = IMAGEMANAGER->findImage("goldNum_w");
			_stageClear.stageRc[i] = RectMakeCenter(_stageClear.rc.left + 130 + (i * 31), _stageClear.rc.top + 30, 28, 31);
		}

		_stageClear.Star[i] = IMAGEMANAGER->findImage("star");
		_stageClear.starRc[i] = RectMakeCenter(0, 0, 0, 0);
	}

	for (int i = 0; i < 8; i++)
	{
		_stageClear.gold[i] = NULL;
		_stageClear.gRc[i] = RectMakeCenter(_stageClear.rc.left + 300 + (i * 22), _stageClear.rc.bottom - 170, 22, 24);
	}

	_stop = _stop2 = false;
	_gold = DATABASE->getElementData()->gold;
	_bossAppear = false;
	_isStop = false;

	//pause
	_pause.window = IMAGEMANAGER->findImage("pause");
	_pause.resume = IMAGEMANAGER->findImage("resume");
	_pause.giveUp = IMAGEMANAGER->findImage("giveUp");
	_pause.wRc = RectMakeCenter(0, 0, 0, 0);
	_pause.rRc = RectMakeCenter(0, 0, 0, 0);
	_pause.gRc = RectMakeCenter(0, 0, 0, 0);
	_pause.gFrameX = _pause.rFrameX = 0;
	_psPuaseFrameX = 0; 
	_puaseClick = false;

	//레벨
	_level = DATABASE->getElementData()->level;
	_levelCell.rc = RectMake(35, 7, 10, 11);
	_levelCell.img = IMAGEMANAGER->findImage("psNumLevel");
	_levelCell.num = 1;
	_levelCell.frameX = 11;

	//골드
	_gold = DATABASE->getElementData()->gold;
	_getGold = 0;

	for (int i = 0; i < 5; i++)
	{
		_goldCell[i].rc = RectMake(CENTERX + 280 + (i * 19), 8, 19, 20);
		_goldCell[i].img = IMAGEMANAGER->findImage("psNumGold");
		_goldCell[i].num = 0;
		_goldCell[i].frameX = 11;
	}

	_playTime = 0;

	//몬스터
	_countEnemy = 0;
	_minSpeed = 100;
	_maxSpeed = 500;
	_countEnemyMax = RND->getFromIntTo(_minSpeed, _maxSpeed);
	_monsterNum = 4;

	_vUnitSlot.clear();

	return S_OK;
}

void threeStageScene::release()
{
	_soldier->release();
	SAFE_DELETE(_soldier);

	_paladog->release();
	SAFE_DELETE(_paladog);
}

void threeStageScene::update()
{
	
	pauseClick();

	if (!_isStop)
	{
		if (!_isPause)
		{
			_playTime += TIMEMANAGER->getElapsedTime();

			_paladog->update();

			for (_viUnitSlot = _vUnitSlot.begin(); _viUnitSlot != _vUnitSlot.end(); ++_viUnitSlot)
			{
				_viUnitSlot->rc = RectMakeCenter(_viUnitSlot->x, _viUnitSlot->y, 100, 90);
			}

			_count++;
			_countEnemy++;

			if (_count % 150 == 0)
			{
				slotUpdate();
				_count = 0;
			}

			if (_countEnemy % _countEnemyMax == 0 && !_bossAppear)
			{
				int rndNum = RND->getInt(_monsterNum);
				if (rndNum == 0) _soldier->createSoldier("Devil", pointMake(WINSIZEX, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage + 5);
				if (rndNum == 1) _soldier->createSoldier("Ghost", pointMake(WINSIZEX, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage + 4);
				if (rndNum == 2) _soldier->createSoldier("Zombie", pointMake(WINSIZEX, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage + 3);
				if (rndNum == 3) _soldier->createSoldier("Witch", pointMake(WINSIZEX, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage + 7);
				_countEnemy = 0;
				_countEnemyMax = RND->getFromIntTo(_minSpeed, _maxSpeed);
			}

			if (_soldier->getKAttack())
			{
				for (int i = 0; i < 2; i++)
				{
					_soldier->createSoldier("Zombie", pointMake(_soldier->getkingX() + RND->getFromIntTo(-30, 30), CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage + 3);
				}

				_soldier->setKAttack(false);
			}

			enemyCountSpeed();
			_soldier->update();
			_deathGauge->update();
			_deathGauge->setGauge(_soldier->getDeathCount(), 50);
			slotMove();
			keyControl();
		}
	}

	setGold(); 
	levelUpdate();
	goldUpdate();
	setStar();
	stageClear();
	setPause();
	pauseWindowClick();

}

void threeStageScene::render()
{
	IMAGEMANAGER->loopRender("ThreeStageScene", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _offsetX, 0);

	_soldier->render();
	_paladog->render();

	//UI 데코중...
	IMAGEMANAGER->render("psPause", getMemDC(), _psPause.left, _psPause.top);
	IMAGEMANAGER->render("psUiTop3", getMemDC(), CENTERX - 120, 5);
	IMAGEMANAGER->render("psLevel", getMemDC(), 10, 5);
	
	for (_viUnitSlot = _vUnitSlot.begin(); _viUnitSlot != _vUnitSlot.end(); ++_viUnitSlot)
	{
		_viUnitSlot->image->render(getMemDC(), _viUnitSlot->rc.left, _viUnitSlot->rc.top);

	}

	_deathGauge->render();

	//Clear
	if (_isClear)
	{
		_stageClear.window->render(getMemDC(), _stageClear.rc.left, _stageClear.rc.top);
	
		for (int i = 0; i <= _useStar; i++)
		{
			if (_useStar != 0)	
				_stageClear.Star[i - 1]->render(getMemDC(), _stageClear.starRc[i - 1].left, _stageClear.starRc[i - 1].top);
		}
		
		for (int i = 0; i < 8; i++)
		{
			if (_stageClear.gold[i] != NULL)
			{
				_stageClear.gold[i]->frameRender(getMemDC(), _stageClear.gRc[i].left, _stageClear.gRc[i].top, _stageClear.gFrameX[i], 0);
			}
		}
		
		for (int i = 0; i < 2; i++)
		{
			if (i < 2)
				_stageClear.stageNum[i]->frameRender(getMemDC(), _stageClear.stageRc[i].left, _stageClear.stageRc[i].top, (i * 4), 0);
		}

		_stageClear.btn->frameRender(getMemDC(), _stageClear.bRc.left, _stageClear.bRc.top, _stageClear.bFrameX, 0);
	}
	
	//puase
	if (_isPause)
	{
		_pause.window->render(getMemDC(), _pause.wRc.left, _pause.wRc.top);
		_pause.resume->frameRender(getMemDC(), _pause.rRc.left, _pause.rRc.top, _pause.rFrameX, 0);
		_pause.giveUp->frameRender(getMemDC(), _pause.gRc.left, _pause.gRc.top, _pause.gFrameX, 0);
	}

	//gold , level
	goldLevelRender();
	
}

void threeStageScene::keyControl()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vUnitSlot.size(); i++)
		{

			if (PtInRect(&_vUnitSlot[i].rc, _ptMouse))
			{
				switch (_vUnitSlot[i].unitNum)
				{
				case 0:
					_soldier->createSoldier("Mouse", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->mouseSpeed / 10, 0, DATABASE->getElementData()->mouseAttack);
					break;

				case 1:
					_soldier->createSoldier("Rabbit", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->rabbitSpeed / 10, 150, DATABASE->getElementData()->rabbitAttack);
					break;

				case 2:
					_soldier->createSoldier("Bear", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->bearSpeed / 10, 0, DATABASE->getElementData()->bearAttack);
					break;

				case 3:
					_soldier->createSoldier("Kangaroo", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->kangarooSpeed / 10, 0, DATABASE->getElementData()->kangarooAttack);
					break;
				case 4:
					_paladog->fireSkill(); 
					break;
				case 5:
					_paladog->punchSkill(); 
					break;
				case 6:
					_paladog->meteoSkill();
					break;
				}
				_vUnitSlot.erase(_vUnitSlot.begin() + i);
			}

		}

	}


}

void threeStageScene::slotUpdate()
{
	if (_vUnitSlot.size() < 8)
	{
		tagunitslot unitSlot;
		ZeroMemory(&unitSlot, sizeof(unitSlot));
		unitSlot.unitNum = RND->getInt(7);
	
		switch (unitSlot.unitNum)
		{
		case 0:
			unitSlot.image = IMAGEMANAGER->findImage("MouseWeapon");
			break;
		case 1:
			unitSlot.image = IMAGEMANAGER->findImage("RabbitWeapon");
			break;
		case 2:
			unitSlot.image = IMAGEMANAGER->findImage("BearWeapon");
			break;
		case 3:
			unitSlot.image = IMAGEMANAGER->findImage("KangarooWeapon");
			break;
		case 4:
			unitSlot.image = IMAGEMANAGER->findImage("3StageFire");
			break;
		case 5:
			unitSlot.image = IMAGEMANAGER->findImage("3StagePunch");
			break;
		case 6:
			unitSlot.image = IMAGEMANAGER->findImage("3StageMeteo");
			break;
		}

		unitSlot.x = 890;
		unitSlot.y = 450;
		unitSlot.rc = RectMakeCenter(unitSlot.x, unitSlot.y, 100, 90);

		_vUnitSlot.push_back(unitSlot);
	}
}

void threeStageScene::slotMove()
{
	RECT rc;

	for (_viUnitSlot = _vUnitSlot.begin(); _viUnitSlot != _vUnitSlot.end(); ++_viUnitSlot)
	{
		if (_viUnitSlot->x >= 100)
		{
			if (_viUnitSlot != _vUnitSlot.begin())
			{
				if (IntersectRect(&rc, &_viUnitSlot->rc, &(_viUnitSlot - 1)->rc))
				{
					_viUnitSlot->x = (_viUnitSlot - 1)->x + 99;
				}
				else
				{
					_viUnitSlot->x -= 3;
				}
			}
			else
				_viUnitSlot->x -= 3;
		}
	}
}

void threeStageScene::stageClear()
{
	if (_soldier->getKingDie())
	{
		_isClear = true;
		_isStop = true;
	}

	if (_isClear)
	{
		_stageClear.window = IMAGEMANAGER->findImage("clearWindow");
		_stageClear.rc = RectMakeCenter(CENTERX, CENTERY, _stageClear.window->getWidth(), _stageClear.window->getHeight());
		_stageClear.btn = IMAGEMANAGER->findImage("btnNext");
		_stageClear.bRc = RectMakeCenter(_stageClear.rc.right - _stageClear.btn->getFrameWidth() / 2,
			_stageClear.rc.bottom,
			_stageClear.btn->getFrameWidth(),
			_stageClear.btn->getHeight());
	
		for (int i = 0; i < 3; i++)
		{
			if (i < 2)
			{
				_stageClear.stageNum[i] = IMAGEMANAGER->findImage("goldNum_w");
				_stageClear.stageRc[i] = RectMakeCenter(_stageClear.rc.left + 130 + (i * 31), _stageClear.rc.top + 30, 28, 31);
			}

			_stageClear.Star[i] = IMAGEMANAGER->findImage("star");
			_stageClear.starRc[i] = RectMakeCenter(_stageClear.rc.left + 155 + (i * 95), _stageClear.rc.bottom - 80, _stageClear.Star[i]->getWidth(), _stageClear.Star[i]->getHeight());
		}

		for (int i = 0; i < 8; i++)
		{
			_stageClear.gRc[i] = RectMakeCenter(_stageClear.rc.left + 300 + (i * 22), _stageClear.rc.bottom - 170, 22, 24);
		}
	}

	clearClick();
}

void threeStageScene::clearClick()
{
	if (PtInRect(&_stageClear.bRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_stageClear.bFrameX = 1;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (_stageClear.bFrameX == 1)
			{
				_stageClear.bFrameX = 0;
				setDatabase();
				SCENEMANAGER->changeScene("stageSelectScene");
			}
		}
	}
	else
	{
		_stageClear.bFrameX = 0;
	}
}

void threeStageScene::setStar()
{
	char str[32];
	int size;
	if (_paladog->getHp() >= (_paladog->getMaxHp() / 10) * 8) _useStar = 3;
	else if (_paladog->getHp() >= (_paladog->getMaxHp() / 10) * 5) _useStar = 2;
	else if (_paladog->getHp() >= (_paladog->getMaxHp() / 10) * 3) _useStar = 1;
	else if (_paladog->getHp() <= 0) _useStar = 0;

	if (_useStar == 3) _bonusGold = 1000;
	else if (_useStar == 2) _bonusGold = 500;
	else if (_useStar == 1) _bonusGold = 200;
	else if (_useStar == 0) _bonusGold = 0;

	sprintf_s(str, "%d", _bonusGold);
	size = strlen(str);

	for (int i = 0; i < 8; i++)
	{
		if (i < size)
		{
			_stageClear.gold[i] = IMAGEMANAGER->findImage("upUnitNum");
			_stageClear.gFrameX[i] = (int)(str[i]) - 46;
		}
		else
		{
			_stageClear.gold[i] = NULL;
			_stageClear.gFrameX[i] = 0;
		}
	}
}

void threeStageScene::setDatabase()
{
	DATABASE->setGold(_gold + _bonusGold);

	switch (DATABASE->getElementData()->nowPlayStage)
	{
	case 0:
		DATABASE->setStageStar1(_useStar);
		break;
	case 1:
		DATABASE->setStageStar2(_useStar);
		break;
	case 2:
		DATABASE->setStageStar3(_useStar);
		break;
	case 3:
		DATABASE->setStageStar4(_useStar);
		break;
	case 4:
		DATABASE->setStageStar5(_useStar);
		break;
	case 5:
		DATABASE->setStageStar6(_useStar);
		break;
	case 6:
		DATABASE->setStageStar7(_useStar);
		break;
	case 7:
		DATABASE->setStageStar8(_useStar);
		break;
	case 8:
		DATABASE->setStageStar9(_useStar);
		break;
	case 9:
		DATABASE->setStageStar10(_useStar);
		break;
	case 10:
		DATABASE->setStageStar11(_useStar);
		break;
	case 11:
		DATABASE->setStageStar12(_useStar);
		break;
	}

	// currentStage 셋팅.
	if (DATABASE->getElementData()->currentStage == DATABASE->getElementData()->nowPlayStage + 1)
		DATABASE->setCurrentStage(DATABASE->getElementData()->currentStage + 1);


	// playTime 저장.
	DATABASE->setPlayTime(DATABASE->getElementData()->playTime + (int)_playTime);


	// 레벨업
	if (DATABASE->getElementData()->level < 20)
	{
		DATABASE->setLevel(DATABASE->getElementData()->level + 1);

		// skillpoint
		DATABASE->setSkillPoint(DATABASE->getElementData()->skillPoint + 1);
	}

	DATABASE->saveDatabase();
}

void threeStageScene::setGold()
{
	_gold += _soldier->getGold();
	_soldier->setGold();
}

void threeStageScene::enemyCountSpeed()
{
	if (_soldier->getDeathCount() == 20 && !_stop)
	{
		for (int i = 0; i < 10; i++)
		{
			_soldier->createSoldier("Devil", pointMake(WINSIZEX, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, 5 + DATABASE->getElementData()->nowPlayStage);
		}
		_stop = true;
	}
	else if (_soldier->getDeathCount() == 40 && !_stop2)
	{
		for (int i = 0; i < 15; i++)
		{
			_soldier->createSoldier("Devil", pointMake(WINSIZEX, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, 5 + DATABASE->getElementData()->nowPlayStage);
		}
		_stop2 = true;
	}
	else if (_soldier->getDeathCount() == 50 && !_bossAppear)
	{
		_bossAppear = true;
		_soldier->createSoldier("Kzombie", pointMake(WINSIZEX, -70), -1.f, 0, 50);
	}

}

void threeStageScene::setPause()
{
	if (_isPause)
	{
		_pause.wRc = RectMakeCenter(CENTERX, CENTERY, _pause.window->getWidth(), _pause.window->getHeight());
		_pause.rRc = RectMakeCenter(CENTERX, CENTERY - 25, _pause.resume->getFrameWidth(), _pause.resume->getHeight());
		_pause.gRc = RectMakeCenter(CENTERX, CENTERY + 80, _pause.giveUp->getFrameWidth(), _pause.giveUp->getHeight());
	}
	else
	{
		_pause.wRc = RectMakeCenter(0,0,0,0);
		_pause.rRc = RectMakeCenter(0,0,0,0);
		_pause.gRc = RectMakeCenter(0,0,0,0);
	}
	
}

void threeStageScene::pauseClick()
{
	if (PtInRect(&_psPause, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isPause = true;
		}
	}
}

void threeStageScene::pauseWindowClick()
{
	if (PtInRect(&_pause.rRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pause.rFrameX = 1;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) )
		{
			if (_pause.rFrameX == 1)
			{
				_pause.rFrameX = 0;
				_isPause = false;
			}
		}
	}
	else
	{
		_pause.rFrameX = 0;
	}

	if(PtInRect(&_pause.gRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pause.gFrameX = 1;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (_pause.gFrameX == 1)
			{
				_pause.gFrameX = 0;

				DATABASE->setGold(_gold);
				DATABASE->saveDatabase();

				SCENEMANAGER->changeScene("stageSelectScene");
			}
		}
	}
	else
	{
		_pause.gFrameX = 0;
	}
	
}

void threeStageScene::levelUpdate()
{
	_levelCell.frameX = _level;
}

void threeStageScene::goldUpdate()
{
	for (int i = 0; i < 5; i++)
	{
		_goldCell[0].num = (int)_gold / 10000;
		_goldCell[1].num = ((int)_gold % 10000) / 1000;
		_goldCell[2].num = ((int)_gold % 1000) / 100;
		_goldCell[3].num = ((int)_gold % 100) / 10;
		_goldCell[4].num = (int)_gold % 10;

		if (_goldCell[0].num == 0)
		{
			_goldCell[0].frameX = 11;
		
			if (_goldCell[1].num == 0)	_goldCell[1].frameX = 11;

		}
		_goldCell[i].frameX = _goldCell[i].num;
	}
}

void threeStageScene::goldLevelRender()
{
	IMAGEMANAGER->render("psLevel", getMemDC(), 10, 5);
	IMAGEMANAGER->render("psMoney", getMemDC(), CENTERX + 250, 5);

	_levelCell.img->frameRender(getMemDC(), _levelCell.rc.left, _levelCell.rc.top, _levelCell.frameX, 0);

	for (int i = 0; i < 5; i++)
	{
		_goldCell[i].img->frameRender(getMemDC(), _goldCell[i].rc.left, _goldCell[i].rc.top, _goldCell[i].frameX, 0);
	}
}