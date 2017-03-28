#include "stdafx.h"
#include "playScene.h"


playScene::playScene()
{
}


playScene::~playScene()
{
}

HRESULT playScene::init()
{
	_soldier = new soldierManager;
	_soldier->init();

	_paladog = new paladog;
	_paladog->init();

	_soldier->setPaladogMemoryLink(_paladog);
	
	for (int i = 0; i < 9; i++)
	{
		_soldierSlot[i].rc = RectMake(21 + 102 * i, 334, 100, 100);
		_soldierSlot[i].img = IMAGEMANAGER->findImage("slot_1");
		_soldierSlot[i].frameX = 0;
		_soldierSlot[i].food = 10 * (i + 1);

		_soldierSlot[i].delay = false;
		_soldierSlot[i].delayCount = 0;
		_soldierSlot[i].delayMaxCount = 70;
	}

	_soldierSlot[0].frameX = 1;
	_soldierSlot[1].frameX = 1;
	_soldierSlot[2].frameX = 1;
	_soldierSlot[3].frameX = 1;
	_soldierSlot[1].img = IMAGEMANAGER->findImage("slot_2");
	_soldierSlot[2].img = IMAGEMANAGER->findImage("slot_3");
	_soldierSlot[3].img = IMAGEMANAGER->findImage("slot_4");

	//배경
	_map = IMAGEMANAGER->findImage("playSceneBackground");
	_offsetX = 0;
	_maxOffsetX = _map->getWidth() - WINSIZEX;

	//일시정지용
	_psPause = RectMake(890, 5, 62, 56);
	_isPause = false;

	//mp, food
	_foodMaxGauge = _paladog->getMaxFood();
	_foodGauge = _paladog->getFood();
	_mpMaxGauge = _paladog->getMaxMp();
	_mpGauge = _paladog->getMp();
	_subFood = _subMp = 0;

	for (int i = 0; i < GAUGEMAX; i++)
	{
		_psFood[i].size = GAUGEMAX / _foodMaxGauge;
		_psFood[i].rc = RectMake(0, 0, 0, 0);
		_psFood[i].img = IMAGEMANAGER->findImage("psEmpty");
		_psFood[i].being = false;
	}

	for (int i = 0; i < GAUGEMAX; i++)
	{
		_psMp[i].size = GAUGEMAX / _mpMaxGauge;
		_psMp[i].rc = RectMake(0, 0, 0, 0);
		_psMp[i].img = IMAGEMANAGER->findImage("psEmpty");
		_psMp[i].being = false;
	}

	//숫자 이미지로 보이기
	for (int i = 0; i < 3; i++)
	{
		_psFoodNum[i].rc = RectMake(84 + (i * 19), 290, 19, 20);
		_psFoodNum[i].img = IMAGEMANAGER->findImage("psNum");
		_psFoodNum[i].num = 0;
		_psFoodNum[i].frameX = 11;

		_psFoodNumMax[i].rc = RectMake(165 + (i * 19), 290, 19, 20);
		_psFoodNumMax[i].img = IMAGEMANAGER->findImage("psNum");
		_psFoodNumMax[i].num = 0;
		_psFoodNumMax[i].frameX = 11;

		_psMpNum[i].rc = RectMake(734 + (i * 19), 290, 19, 20);
		_psMpNum[i].img = IMAGEMANAGER->findImage("psNum");
		_psMpNum[i].num = 0;
		_psMpNum[i].frameX = 11;

		_psMpNumMax[i].rc = RectMake(815 + (i * 19), 290, 19, 20);
		_psMpNumMax[i].img = IMAGEMANAGER->findImage("psNum");
		_psMpNumMax[i].num = 0;
		_psMpNumMax[i].frameX = 11;
	}
	
	//left, right
	_leftBtnRc = RectMake(90, 460, 108, 60);
	_rightBtnRc = RectMake(270, 460, 108, 60);
	_leftBtnFrameX = _rightBtnFrameX = 0;

	//hp
	_currentGaugeWidth = 79;
	_palaHpWidth = 79;
	_bossHpWidth = 79;

	_paladogTotal = RectMake(389, 10, _currentGaugeWidth, 11);
	_paladogCurrent = RectMake(389, 10, _palaHpWidth, 11);

	_bossTotal = RectMake(490, 10, _currentGaugeWidth, 11);
	_bossCurrent = RectMake(490, 10, _bossHpWidth, 11);

	_palaTotalhp = _paladog->getMaxHp();
	_palaCurrentHp = _paladog->getHp();
	_palaHpRatio = _palaCurrentHp /_palaTotalhp; 

	_bossTotalhp = 2000; //임시로 적어놓음
	_bossCurrentHp = 2000;  //임시로 적어놓음
	_bossHpRatio = _bossCurrentHp / _bossTotalhp;
	_bossDemage = 0; //임시로 적어놓음

	_soldier->setBossHp(_bossTotalhp);

	//보스
	_boss.x = WINSIZEX + 300;
	_boss.y = 0;
	_boss.rc = RectMake(_boss.x, _boss.y, 300, 364);
	_boss.img = IMAGEMANAGER->findImage("bossHome");
	_boss.imgUp = IMAGEMANAGER->findImage("bossHomeUp");
	_boss.state = BOSS_NORMAL;
	_boss.power = 0;

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

	//스킬
	for (int i = 0; i < 3; i++)
	{
		_skill[i].rc = RectMake(512 + 102 * i, 427, 102, 102);

		if (i !=0) _skill[i].rc = RectMake(513 + 102 * i + (53 - 2*i) * i, 427, 102, 102);

		_skill[i].frameX = 0;
	}

	_skill[0].skill= 7;
	_skill[1].skill = 10;
	_skill[2].skill = 38;
	_skill[0].img = IMAGEMANAGER->findImage("psPunch");
	_skill[1].img = IMAGEMANAGER->findImage("psFire");
	_skill[2].img = IMAGEMANAGER->findImage("psMeteo");

	//clear
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

	//pause
	_pause.window = IMAGEMANAGER->findImage("pause");
	_pause.resume = IMAGEMANAGER->findImage("resume");
	_pause.giveUp = IMAGEMANAGER->findImage("giveUp");
	_pause.wRc = RectMakeCenter(0, 0, 0, 0);
	_pause.rRc = RectMakeCenter(0, 0, 0, 0);
	_pause.gRc = RectMakeCenter(0, 0, 0, 0);
	_pause.gFrameX = _pause.rFrameX = 0;
	


	_playTime = 0;
	//몬스터
	_countEnemy = 0;
	_minSpeed = 100;
	_maxSpeed = 500;
	_countEnemyMax = RND->getFromIntTo(_minSpeed, _maxSpeed);
	_monsterNum = 4;


	return S_OK;
}

void playScene::release()
{
	_soldier->release();
	SAFE_DELETE(_soldier);

	_paladog->release();
	SAFE_DELETE(_paladog);

}

void playScene::update()
{
	pauseClick();

	if (!_isPause)
	{
		_countEnemy++;
		_playTime += TIMEMANAGER->getElapsedTime();

		_soldier->update();
		_paladog->update();

		keyControl();
		slotUpdate();

		foodMpUpdate();
		hpSetting();

		backgroundLoop();
		bossLoop();
		bossSetting();

		levelUpdate();
		goldUpdate();

		skillUpdate();

		btnClickSodier();
		btnClickSkill();

		setStar();
		stageClear();

		if (_countEnemy % _countEnemyMax == 0)
		{
			int rndNum = RND->getInt(_monsterNum);
			if (rndNum == 0) _soldier->createSoldier("Devil", pointMake(1639, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage + 5);
			if (rndNum == 1) _soldier->createSoldier("Ghost", pointMake(1639, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage +  4);
			if (rndNum == 2) _soldier->createSoldier("Zombie", pointMake(1639, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage + 3);
			if (rndNum == 3) _soldier->createSoldier("Witch", pointMake(1639, CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, DATABASE->getElementData()->nowPlayStage + 7);
			_countEnemy = 0;
			_countEnemyMax = RND->getFromIntTo(_minSpeed, _maxSpeed);
		}
	}

	setPause();
	pauseWindowClick();
	setGold();
}

void playScene::render()
{
	_map->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _offsetX, 0);

	//보스집 (아래)
	_boss.img->render(getMemDC(), _boss.rc.left - 100, _boss.rc.top);
	
	_soldier->render();
	_paladog->render();

	//보스 집 (위)
	_boss.imgUp->frameRender(getMemDC(), _boss.rc.left - 100, _boss.rc.top);

	IMAGEMANAGER->render("playSceneSlot", getMemDC(), 0, 270);
	IMAGEMANAGER->frameRender("psLeft", getMemDC(), _leftBtnRc.left, _leftBtnRc.top, _leftBtnFrameX, 0);
	IMAGEMANAGER->frameRender("psRight", getMemDC(), _rightBtnRc.left, _rightBtnRc.top, _rightBtnFrameX, 0);
	
	for (int i = 0; i < 3; i++)
	{
		_skill[i].img->frameRender(getMemDC(), _skill[i].rc.left, _skill[i].rc.top, _skill[i].frameX, 0);
	}

	for (int i = 0; i < 9; i++)
	{
		_soldierSlot[i].img->frameRender(getMemDC(), _soldierSlot[i].rc.left, _soldierSlot[i].rc.top, _soldierSlot[i].frameX, 0);
	}
	
	//UI 데코
	IMAGEMANAGER->render("psPause", getMemDC(), _psPause.left, _psPause.top);
	
	foodMpRender();
	hpRender();
	goldLevelRender();

	//clear
	if (_isClear)
	{
		_stageClear.window->render(getMemDC(), _stageClear.rc.left, _stageClear.rc.top);
		
		for (int i = 0; i <= _useStar; i++)
		{
			if (_useStar != 0)	_stageClear.Star[i - 1]->render(getMemDC(), _stageClear.starRc[i - 1].left, _stageClear.starRc[i - 1].top);
		}

		for (int i = 0; i < 8; i++)
		{
			//Rectangle(getMemDC(), _stageClear.gRc[i].left, _stageClear.gRc[i].top, _stageClear.gRc[i].right, _stageClear.gRc[i].bottom);
			if (_stageClear.gold[i] != NULL)
			{
				_stageClear.gold[i]->frameRender(getMemDC(), _stageClear.gRc[i].left, _stageClear.gRc[i].top, _stageClear.gFrameX[i], 0);
			}
		}
		for (int i = 0; i < 2; i++)
		{
			//Rectangle(getMemDC(), _stageClear.stageRc[i].left, _stageClear.stageRc[i].top, _stageClear.stageRc[i].right, _stageClear.stageRc[i].bottom);
			if (i < 2)	_stageClear.stageNum[i]->frameRender(getMemDC(), _stageClear.stageRc[i].left, _stageClear.stageRc[i].top, (i * 3), 0);
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

	

}

void playScene::keyControl()
{
	// 아군 생성
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		if (_paladog->getFood() >= _soldierSlot[0].food)
		{
			_soldierSlot[0].delay = true;
			_paladog->useFood(_soldierSlot[0].food);
			_subFood = _soldierSlot[0].food;
			_soldier->createSoldier("Mouse", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->mouseSpeed / 10, -20, DATABASE->getElementData()->mouseAttack);
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		if (_paladog->getFood() >= _soldierSlot[1].food)
		{
			_soldierSlot[1].delay = true;
			_paladog->useFood(_soldierSlot[1].food);
			_subFood = _soldierSlot[1].food;
			_soldier->createSoldier("Rabbit", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->rabbitSpeed / 10, 150, DATABASE->getElementData()->rabbitAttack);
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		if (_paladog->getFood() >= _soldierSlot[2].food)
		{
			_soldierSlot[2].delay = true;
			_paladog->useFood(_soldierSlot[2].food);
			_subFood = _soldierSlot[2].food;
			_soldier->createSoldier("Bear", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->bearSpeed / 10, -20, DATABASE->getElementData()->bearAttack);
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{
		if (_paladog->getFood() >= _soldierSlot[3].food)
		{
			_soldierSlot[3].delay = true;
			_paladog->useFood(_soldierSlot[3].food);
			_subFood = _soldierSlot[3].food;
			_soldier->createSoldier("Kangaroo", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->kangarooSpeed / 10, -20, DATABASE->getElementData()->kangarooAttack);
		}
	}

	// 적 생성 테스트용
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_soldier->createSoldier("Devil", pointMake(1639 , CENTERY - RND->getFromIntTo(80, 120)), -1.f, 0, 5 + DATABASE->getElementData()->nowPlayStage);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_soldier->createSoldier("Rabbit", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->rabbitSpeed / 10, 150, DATABASE->getElementData()->rabbitAttack);

	}


	//left, right
	btnUpClickLR();
}


void playScene::slotUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		// 딜레이시간이면 프레임 변경
		if (_soldierSlot[i].delay)
		{
			_soldierSlot[i].delayCount++;
			_soldierSlot[i].frameX = 3;

			if (_soldierSlot[i].delayCount == _soldierSlot[i].delayMaxCount)
			{
				_soldierSlot[i].delay = false;
				_soldierSlot[i].delayCount = 0;
			}
		}

		// 팔라독의 식량이 슬롯식량보다 크면 이미지 프레임 변경
		if (_paladog->getFood() >= _soldierSlot[i].food)
		{
			_soldierSlot[i].frameX = 2;
		}
		else
		{
			_soldierSlot[i].frameX = 1;
		}

	}
}

void playScene::foodMpUpdate()
{
	//food 이미지
	_foodGauge = _paladog->getFood();

	if (_subFood == 0) {
		for (int i = 0; i < _foodGauge; i++)
		{
			_psFood[i].size = GAUGEMAX / _foodMaxGauge;
			_psFood[i].rc = RectMake(74 + (i * _psFood[i].size), 306, _psFood[i].size, 14);
			_psFood[i].img = IMAGEMANAGER->findImage("psFood");
			_psFood[i].being = true;
		}
	}
	else
	{
		for (int i = _foodMaxGauge; i > _foodGauge; i--)
		{
			if (_psFood[i].being = false) continue;
			_psFood[i].rc = RectMake(0, 0, 0, 0);
			_psFood[i].img = IMAGEMANAGER->findImage("psEmpty");
			_psFood[i].being = false;
		}
		_subFood = 0;
	}

	//mp 이미지
	_mpGauge = _paladog->getMp();
	//_subMp = _paladog->getUseMp();

	if (_subMp == 0) {
		for (int i = 0; i < _mpGauge; i++)
		{
			_psMp[i].size = GAUGEMAX / _mpMaxGauge;
			_psMp[i].rc = RectMake(878 - (i * _psMp[i].size), 306, _psMp[i].size, 14);
			_psMp[i].img = IMAGEMANAGER->findImage("psMp");
			_subMp = _paladog->getUseMp();
		}
	}
	else
	{
		for (int i = _mpMaxGauge; i > _mpGauge; i--)
		{
			if (_psMp[i].being = false) continue;
			_psMp[i].rc = RectMake(0, 0, 0, 0);
			_psMp[i].img = IMAGEMANAGER->findImage("psEmpty");
			_psMp[i].being = false;
		}
		_subMp = 0;
	}

	// 숫자
	for (int i = 0; i < 3; i++)
	{
		//current Food
		_psFoodNum[0].num = ((int)_foodGauge % 1000) / 100;
		_psFoodNum[1].num = ((int)_foodGauge % 100) / 10;
		_psFoodNum[2].num = (int)_foodGauge % 10;

		if (_psFoodNum[0].num == 0)
		{
			_psFoodNum[0].frameX = 11;
			if (_psFoodNum[1].num == 0)	_psFoodNum[1].frameX = 11;

		}
		_psFoodNum[i].frameX = _psFoodNum[i].num;

		//max Food
		_psFoodNumMax[0].num = ((int)_foodMaxGauge % 1000) / 100;
		_psFoodNumMax[1].num = ((int)_foodMaxGauge % 100) / 10;
		_psFoodNumMax[2].num = (int)_foodMaxGauge % 10;

		if (_psFoodNumMax[0].num == 0)
		{
			_psFoodNumMax[0].frameX = 11;
			if (_psFoodNumMax[1].num == 0)	_psFoodNumMax[1].frameX = 11;

		}
		_psFoodNumMax[i].frameX = _psFoodNumMax[i].num;

		//current Mp
		_psMpNum[0].num = ((int)_mpGauge % 1000) / 100;
		_psMpNum[1].num = ((int)_mpGauge % 100) / 10;
		_psMpNum[2].num = (int)_mpGauge % 10;

		if (_psMpNum[0].num == 0)
		{
			_psMpNum[0].frameX = 11;
			if (_psMpNum[1].num == 0)	_psMpNum[1].frameX = 11;

		}
		_psMpNum[i].frameX = _psMpNum[i].num;

		//Max Mp
		_psMpNumMax[0].num = ((int)_mpMaxGauge % 1000) / 100;
		_psMpNumMax[1].num = ((int)_mpMaxGauge % 100) / 10;
		_psMpNumMax[2].num = (int)_mpMaxGauge % 10;

		if (_psMpNumMax[0].num == 0)
		{
			_psMpNumMax[0].frameX = 11;
			if (_psMpNumMax[1].num == 0)	_psMpNumMax[1].frameX = 11;

		}
		_psMpNumMax[i].frameX = _psMpNumMax[i].num;

	}

}

void playScene::foodMpRender()
{
	IMAGEMANAGER->render("psUiTop", getMemDC(), CENTERX - 120, 5);

	for (int i = 0; i < _foodMaxGauge; i++)
	{
		_psFood[i].img->render(getMemDC(), _psFood[i].rc.left, _psFood[i].rc.top);
	}

	for (int i = 0; i < _mpMaxGauge; i++)
	{
		_psMp[i].img->render(getMemDC(), _psMp[i].rc.left, _psMp[i].rc.top);
	}

	//슬래시
	IMAGEMANAGER->render("psSlash", getMemDC(), 144, 290);
	IMAGEMANAGER->render("psSlash", getMemDC(), 794, 290);

	//food, mp 숫자이미지 출력
	for (int i = 0; i < 3; i++)
	{
		_psFoodNum[i].img->frameRender(getMemDC(), _psFoodNum[i].rc.left, _psFoodNum[i].rc.top, _psFoodNum[i].frameX, 0);
		_psFoodNumMax[i].img->frameRender(getMemDC(), _psFoodNumMax[i].rc.left, _psFoodNumMax[i].rc.top, _psFoodNumMax[i].frameX, 0);
		_psMpNum[i].img->frameRender(getMemDC(), _psMpNum[i].rc.left, _psMpNum[i].rc.top, _psMpNum[i].frameX, 0);
		_psMpNumMax[i].img->frameRender(getMemDC(), _psMpNumMax[i].rc.left, _psMpNumMax[i].rc.top, _psMpNumMax[i].frameX, 0);
	}

}

void playScene::btnUpClickLR()
{

	if (PtInRect(&_leftBtnRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_leftBtnFrameX = 1;
			_paladog->setGoing(true);
			_paladog->setRight(false);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_leftBtnFrameX = 0;
			_paladog->setGoing(false);
			_paladog->setStayMode(true);

		}
	}
	else if (PtInRect(&_rightBtnRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_rightBtnFrameX = 1;
			_paladog->setGoing(true);
			_paladog->setRight(true);
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_rightBtnFrameX = 0;
			_paladog->setGoing(false);
			_paladog->setStayMode(true);

		}
	}
}

void playScene::hpSetting()
{
	_palaCurrentHp = _paladog->getHp();
	
	_palaHpRatio = (float)_palaCurrentHp / (float)_palaTotalhp;
	
	_palaHpWidth = _currentGaugeWidth * _palaHpRatio;

	if (_palaHpWidth < 0)
		_palaHpWidth = 0;

	_paladogCurrent = RectMake(468, 10, -_palaHpWidth, 11);
	_bossCurrentHp = _soldier->getBossHp();

	_bossHpRatio = (float)_bossCurrentHp / (float)_bossTotalhp;
	_bossHpWidth = _currentGaugeWidth * _bossHpRatio;

	if (_bossHpWidth < 0)
		_bossHpWidth = 0;

	_bossCurrent = RectMake(490, 10, _bossHpWidth, 11);

	if (_bossCurrentHp < 0)
	{
		_isClear = true;
	}
		

}

void playScene::hpRender()
{
	HBRUSH hbrush;
	
	hbrush = CreateSolidBrush(RGB(100, 100, 100));
	Rectangle(getMemDC(), _paladogTotal.left, _paladogTotal.top, _paladogTotal.right, _paladogTotal.bottom);
	FillRect(getMemDC(), &_paladogTotal, hbrush);
	
	Rectangle(getMemDC(), _bossTotal.left, _bossTotal.top, _bossTotal.right, _bossTotal.bottom);
	FillRect(getMemDC(), &_bossTotal, hbrush);
	DeleteObject(hbrush);
		
	hbrush = CreateSolidBrush(RGB(7, 192, 236));
	Rectangle(getMemDC(), _paladogCurrent.left, _paladogCurrent.top, _paladogCurrent.right, _paladogCurrent.bottom);
	FillRect(getMemDC(), &_paladogCurrent, hbrush);
	DeleteObject(hbrush);

	hbrush = CreateSolidBrush(RGB(250, 37, 11));
	Rectangle(getMemDC(), _bossCurrent.left, _bossCurrent.top, _bossCurrent.right, _bossCurrent.bottom);
	FillRect(getMemDC(), &_bossCurrent, hbrush);
	DeleteObject(hbrush);
}

void playScene::backgroundLoop()
{
	if (!_paladog->getStaying())
	{
		if (_paladog->getRc().left > 150 && _offsetX < _maxOffsetX)
		{
			if (_paladog->getRight())
				_offsetX += (int)_paladog->getSpeed();
			else 
				_offsetX -= (int)_paladog->getSpeed();

			_paladog->setX(150);
		}
		else if (_offsetX > 0 && _paladog->getRc().left <150)
		{
			if (_paladog->getRight())	
				_offsetX += (int)_paladog->getSpeed();
			else
				_offsetX -= (int)_paladog->getSpeed();

			_paladog->setX(150);
		}
		else if (_offsetX < 0) _offsetX = 0;
	
		_soldier->setOffsetX(_offsetX);
		_paladog->setOffsetX(_offsetX);
	}
}

void playScene::bossLoop()
{
	if (!_paladog->getStaying())
	{
		if (_paladog->getRight() && _offsetX > _maxOffsetX - 600 && _paladog->getRc().left > 150)
		{
			_boss.x -= (int)_paladog->getSpeed();

			if (_boss.x <= WINSIZEX - 300) 	_boss.x = WINSIZEX - 300;
		}
		
		if (!_paladog->getRight() && _paladog->getRc().left < 150)
		{
			_boss.x += (int)_paladog->getSpeed();

			if (_boss.x >= WINSIZEX + 300)_boss.x = WINSIZEX + 300;
		}
	}

	_boss.rc = RectMake(_boss.x + 100, _boss.y, 300, 364);
	
	_soldier->setAttackRc(_boss.rc);
	
	

}

void playScene::bossSetting()
{
	if (_bossHpWidth > 40) _boss.state = BOSS_NORMAL;
	else if (_bossHpWidth <= 40 && _bossHpWidth > 0) _boss.state = BOSS_WEAK;
	else if (_bossHpWidth <= 0) _boss.state = BOSS_DIE;

	if (_boss.state == BOSS_NORMAL)
	{
		_boss.img = IMAGEMANAGER->findImage("bossHome");
		_boss.imgUp = IMAGEMANAGER->findImage("bossHomeUp");
	}

	else if (_boss.state == BOSS_WEAK)
	{
		_boss.img = IMAGEMANAGER->findImage("bossHomeWeak");
		_boss.imgUp = IMAGEMANAGER->findImage("bossHomeWeakUp");
	}

	else if (_boss.state == BOSS_DIE)
	{
		_boss.img = IMAGEMANAGER->findImage("bossHomeBroken");
		_boss.imgUp = IMAGEMANAGER->findImage("bossHomeBrokenUp");
	}
}

void playScene::levelUpdate()
{
	_levelCell.frameX = _level;
}

void playScene::goldUpdate()
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

void playScene::goldLevelRender()
{
	IMAGEMANAGER->render("psLevel", getMemDC(), 10, 5);
	IMAGEMANAGER->render("psMoney", getMemDC(), CENTERX + 250, 5);

	_levelCell.img->frameRender(getMemDC(), _levelCell.rc.left, _levelCell.rc.top, _levelCell.frameX, 0);

	for (int i = 0; i < 5; i++)
	{
		_goldCell[i].img->frameRender(getMemDC(), _goldCell[i].rc.left, _goldCell[i].rc.top, _goldCell[i].frameX, 0);
	}
}

void playScene::skillUpdate()
{
	for (int i = 0; i < 3; i++)
	{
		if (_paladog->getMp() >= _skill[i].skill)
		{
			_skill[i].frameX = 1;
		}
		else
		{
			_skill[i].frameX = 0;
		}

	}
}

void playScene::btnClickSodier()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_soldierSlot[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (i == 0)
				{
					if (_paladog->getFood() >= _soldierSlot[0].food)
					{
						_soldierSlot[0].delay = true;
						_paladog->useFood(_soldierSlot[0].food);
						_subFood = _soldierSlot[0].food;
						_soldier->createSoldier("Mouse", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->mouseSpeed / 10, -20, DATABASE->getElementData()->mouseAttack);
					}
				}
				else if (i == 1)
				{
					if (_paladog->getFood() >= _soldierSlot[1].food)
					{
						_soldierSlot[1].delay = true;
						_paladog->useFood(_soldierSlot[1].food);
						_subFood = _soldierSlot[1].food;
						_soldier->createSoldier("Rabbit", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->rabbitSpeed / 10, 150, DATABASE->getElementData()->rabbitAttack);
					}
				}
				else if (i == 2)
				{
					if (_paladog->getFood() >= _soldierSlot[2].food)
					{
						_soldierSlot[2].delay = true;
						_paladog->useFood(_soldierSlot[2].food);
						_subFood = _soldierSlot[2].food;
						_soldier->createSoldier("Bear", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->bearSpeed / 10, -20, DATABASE->getElementData()->bearAttack);
					}
				}
				else if (i == 3)
				{
					if (_paladog->getFood() >= _soldierSlot[3].food)
					{
						_soldierSlot[3].delay = true;
						_paladog->useFood(_soldierSlot[3].food);
						_subFood = _soldierSlot[3].food;
						_soldier->createSoldier("Kangaroo", pointMake(0, CENTERY - RND->getFromIntTo(80, 120)), (float)DATABASE->getElementData()->kangarooSpeed / 10, -20, DATABASE->getElementData()->kangarooAttack);
					}
				}
			}
		}
	}
}

void playScene::btnClickSkill()
{
	for (int i = 0; i < 3; i++)
	{
		if (PtInRect(&_skill[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (i == 0)
				{
					if (_paladog->getMp() >= 7)
						_paladog->punchSkill();
				}

				if (i == 1)
				{
					if (_paladog->getMp() >= 10)
						_paladog->fireSkill();
				}

				if (i == 2)
				{
					if (_paladog->getMp() >= 38)
						_paladog->meteoSkill();
				}
			}
		}
	}
}

void playScene::stageClear()
{
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

void playScene::clearClick()
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

void playScene::setStar()
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

void playScene::setPause()
{
	if (_isPause)
	{
		_pause.wRc = RectMakeCenter(CENTERX, CENTERY, _pause.window->getWidth(), _pause.window->getHeight());
		_pause.rRc = RectMakeCenter(CENTERX, CENTERY - 25, _pause.resume->getFrameWidth(), _pause.resume->getHeight());
		_pause.gRc = RectMakeCenter(CENTERX, CENTERY + 80, _pause.giveUp->getFrameWidth(), _pause.giveUp->getHeight());
	}
	else
	{
		_pause.wRc = RectMakeCenter(0, 0, 0, 0);
		_pause.rRc = RectMakeCenter(0, 0, 0, 0);
		_pause.gRc = RectMakeCenter(0, 0, 0, 0);
	}
}

void playScene::pauseClick()
{
	if (PtInRect(&_psPause, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isPause = true;
		}
	}
}

void playScene::pauseWindowClick()
{
	if (PtInRect(&_pause.rRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pause.rFrameX = 1;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
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

	if (PtInRect(&_pause.gRc, _ptMouse))
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

void playScene::setGold()
{
	_gold += _soldier->getGold();
	_soldier->setGold();
}

void playScene::setDatabase()
{
	// 돈 저장
	DATABASE->setGold(_gold + _bonusGold);

	// 현재 스테이지 별 저장.
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

	// 데이터베이스 저장...
	DATABASE->saveDatabase();
}
