#include "stdafx.h"
#include "startScene.h"


startScene::startScene()
{
}


startScene::~startScene()
{
}

HRESULT startScene::init()
{
	_startBtn = RectMake(20, 370, 280, 155);
	
	_selectSlot = RectMake(282, 0, 678, 540);
	_selectSlotCloseBtn = RectMake(875, 0, 81, 81);

	_selectPlayerNum = MAXPLAYER;

	_isStart = false;

	_offsetX = _offsetY = 0;
	
	_count = _currentFrameX = 0;
	_startBtnFrameY = _closeBtnFrameX = 0;

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j < 2)
			{
				_infoList[i].lvImage[j] = NULL;
				_infoList[i].stImage[j] = NULL;
			}

			if(j < 6)	
				_infoList[i].timeIamge[j] = NULL;
				_infoList[i].goldImage[j] = NULL;
		}
	}

	playerDataInit();

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	keyControl();
	frameCount();
	showImageInfo();
	
}

void startScene::render()
{
	// 기본 백그라운드
	IMAGEMANAGER->findImage("main_cloud_top")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, 122), _offsetX, 0);
	IMAGEMANAGER->findImage("main_cloud_bottom")->loopRender(getMemDC(), &RectMake(0, 122, WINSIZEX, 122), -_offsetX, 0);
	IMAGEMANAGER->frameRender("main_vol", getMemDC(), 312, 244, _currentFrameX, 0);
	IMAGEMANAGER->render("main_mountain_big", getMemDC(), -216, 140);
	IMAGEMANAGER->render("main_mountain_small", getMemDC(), 710, 350);
	IMAGEMANAGER->frameRender("stand_dog", getMemDC(), 82, 20, _currentFrameX, 0);
	IMAGEMANAGER->render("main_logo", getMemDC(), 250, 10);
	IMAGEMANAGER->render("tree", getMemDC(), 0, 170);

	// 시작버튼 눌렀을떄 보이는 것들
	if (_isStart)
	{
		IMAGEMANAGER->render("selectSlot", getMemDC(), _selectSlot.left, _selectSlot.top);
		IMAGEMANAGER->frameRender("selectSlotCloseBtn", getMemDC(), _selectSlotCloseBtn.left, _selectSlotCloseBtn.top, _closeBtnFrameX, 0);
	
		for (int i = 0; i < MAXPLAYER; i++)
		{			
			if (_playerList[i].isSelect)
			{		
				IMAGEMANAGER->render("startBtn", getMemDC(), _playerList[i].rc.right - 25, _playerList[i].rc.top + 20);
				
				if (!_playerList[i].isEmpty)
					IMAGEMANAGER->render("deleteBtn", getMemDC(), _playerList[i].rc.right - 25, _playerList[i].rc.top + 80);
			}

			if (_playerList[i].isEmpty)
			{
				IMAGEMANAGER->render("playerListEmpty", getMemDC(), _playerList[i].rc.left, _playerList[i].rc.top);
			}
			else
			{
				IMAGEMANAGER->render("playerList", getMemDC(), _playerList[i].rc.left, _playerList[i].rc.top);
			}

		}
	}
	else // 시작버튼 안눌렀을때 보이는 것들
	{
		IMAGEMANAGER->frameRender("playBtn", getMemDC(), _startBtn.left, _startBtn.top,0,_startBtnFrameY);
	}

	if (_isStart)
	{
		for (int i = 0; i < MAXPLAYER; i++)
		{
			if (!_playerList[i].isEmpty)
			{
				for (int j = 0; j < 2; j++)
				{
					if (_infoList[i].lvImage[j] != NULL)
					_infoList[i].lvImage[j]->frameRender(getMemDC(), _infoList[i].lvRc[j].left, _infoList[i].lvRc[j].top, _infoList[i].levFrameX[j], 0);
					
					if (_infoList[i].stImage[j] != NULL)
					_infoList[i].stImage[j]->frameRender(getMemDC(), _infoList[i].stRc[j].left, _infoList[i].stRc[j].top, _infoList[i].stFrameX[j], 0);
				}
				for (int j = 0; j < 8; j++)
				{
					if (_infoList[i].goldImage[j] != NULL)
						_infoList[i].goldImage[j]->frameRender(getMemDC(), _infoList[i].goldRc[j].left, _infoList[i].goldRc[j].top, _infoList[i].goldFrameX[j], 0);
					if (j < 6)
						if (_infoList[i].timeIamge[j] != NULL)
							_infoList[i].timeIamge[j]->frameRender(getMemDC(), _infoList[i].timeRc[j].left, _infoList[i].timeRc[j].top, _infoList[i].timeFrameX[j], 0);
				}
			}
		}
	}
}

void startScene::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_isStart)
		{
			if (PtInRect(&_startBtn, _ptMouse))
			{
				_startBtnFrameY = 1;
				setInfo();
			}
		}
		else
		{
			if (PtInRect(&_selectSlotCloseBtn, _ptMouse))
			{
				_closeBtnFrameX = 1;
			}

			for (int i = 0; i < MAXPLAYER; i++)
			{
				// 시작버튼 클릭
				if (PtInRect(&_playerList[i].selectRc, _ptMouse))
				{
					// 비어있는 플레이어창이면
					if (_playerList[i].isEmpty)
					{
						// 파일 생성...
						createPlayerData(_playerList[i].fileName);
						DATABASE->init(_playerList[i].fileName);

						// 새로운 플레이어 창으로 이동
						SCENEMANAGER->changeScene("newPlayerScene");
					}
					else
					{
						// 데이터 불러와야지...
						DATABASE->init(_playerList[i].fileName);

						// 스테이지 선택 창으로 이동... 
						SCENEMANAGER->changeScene("stageSelectScene");
					}
					
				}

				// 삭제버튼 클릭
				if (PtInRect(&_playerList[i].deleteRc, _ptMouse))
				{
					// 삭제한다.
					deletePlayerData(_playerList[i].fileName);
					// 초기화
					playerDataInit();
				}

			}

			for (int i = 0; i < MAXPLAYER; i++)
			{
				if (PtInRect(&_playerList[i].rc, _ptMouse))
				{
					_playerList[i].x = 275;
					_playerList[i].rc = RectMake(_playerList[i].x, _playerList[i].y, 590, 160);
					
					_playerList[i].isSelect = true;
					setInfo();
					// 셀렉트 rc
					_playerList[i].selectRc = RectMake(_playerList[i].rc.right - 25, _playerList[i].rc.top + 20, 107, 54);
					// 비어있는창이 아니면 델리트도
					if(!_playerList[i].isEmpty)
						_playerList[i].deleteRc = RectMake(_playerList[i].rc.right - 25, _playerList[i].rc.top + 80, 107, 54);

				}
				else
				{
					_playerList[i].x = 330;
					_playerList[i].rc = RectMake(_playerList[i].x, _playerList[i].y, 590, 160);

					_playerList[i].isSelect = false;

					// 셀렉트, 델리트 rc 초기화
					_playerList[i].selectRc = RectMake(0,0,0,0);
					_playerList[i].deleteRc = RectMake(0,0,0,0);

				}
			}
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (!_isStart)
		{
			if (PtInRect(&_startBtn, _ptMouse))
			{
				_startBtnFrameY = 0;
				_isStart = !_isStart;
			}
			else
			{
				_startBtnFrameY = 0;
			}
		}
		else
		{
			if (PtInRect(&_selectSlotCloseBtn, _ptMouse))
			{
				_closeBtnFrameX = 0;
				_isStart = !_isStart;
			}
			else
			{
				_closeBtnFrameX = 0;
			}
		}
	}
}

void startScene::frameCount()
{
	_count++;

	if (_count % 2 == 0)
	{
		_offsetX++;
		if (_count % 7 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX > IMAGEMANAGER->findImage("main_vol")->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
		}
	}

}

void startScene::playerDataInit()
{
	// 초기화하고
	for (int i = 0; i < MAXPLAYER; i++)
	{
		_playerList[i].x = 330;
		_playerList[i].y = 80 + i * 139 + i * 10;

		_playerList[i].rc = RectMake(_playerList[i].x, _playerList[i].y, 590, 160);

		_playerList[i].isEmpty = true;
		_playerList[i].isSelect = false;

		_playerList[i].selectRc = RectMake(0, 0, 0, 0);
		_playerList[i].deleteRc = RectMake(0, 0, 0, 0);


		sprintf_s(_playerList[i].fileName, "player0%d.txt", i + 1);

		// 셋팅해준다.
		if (TXTDATA->txtLoad(_playerList[i].fileName).size() != 0)
		{
			_playerList[i].isEmpty = false;
			//데이터 불러옴...
			loadPlayerData(_playerList[i].fileName, i);
		}
	}


}

void startScene::loadPlayerData(const char* fileName, int i)
{
	DATABASE->init(fileName);

	 _playerList[i].lev = DATABASE->getElementData()->level;
	 _playerList[i].star = DATABASE->getElementData()->starTotal;
	 _playerList[i].gold = DATABASE->getElementData()->gold;
	 _playerList[i].time = DATABASE->getElementData()->playTime;
}

void startScene::createPlayerData(const char* fileName)
{
	vector<string> vStr;
	
	// 기본정보 LEVEL, 별, 머니
	vStr.push_back("1, 0, 10000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0");
	
	// 쥐
	vStr.push_back("1, 50, 3, 8, 70, 3, 10, 100");
	
	// 토끼
	vStr.push_back("1, 75, 5, 5, 70, 5, 10, 500");
	
	// 곰
	vStr.push_back("1, 100, 7, 5, 70, 7, 10, 1000");
	
	// 캥거루
	vStr.push_back("1, 120, 9, 5, 70, 5, 10, 1500");

	// 플레이어 정보
	vStr.push_back("100, 100, 100, 30, 30, 0, 0, 0, 0, 0, 0");

	// 파일생성
	TXTDATA->txtSave(fileName, vStr);
}

void startScene::deletePlayerData(const char* fileName)
{
	DeleteFile(fileName);
}

void startScene::setInfo()
{
	for (int i = 0; i < MAXPLAYER; i++)
	{
		if (!_playerList[i].isEmpty)
		{
			for (int j = 0; j < 2; j++)
			{
				_infoList[i].lvImage[j] = IMAGEMANAGER->findImage("levUpnum");
				_infoList[i].lvRc[j] = RectMake(_playerList[i].rc.left + 120 + (j *  _infoList[i].lvImage[j]->getFrameWidth()),
					_playerList[i].rc.top + 15,
					_infoList[i].lvImage[j]->getFrameWidth(),
					_infoList[i].lvImage[j]->getFrameHeight());
				_infoList[i].stImage[j] = IMAGEMANAGER->findImage("levUpnum");
				_infoList[i].stRc[j] = RectMake(_playerList[i].rc.right - 120 + (j *  _infoList[i].stImage[j]->getFrameWidth()),
					_playerList[i].rc.top + 15,
					_infoList[i].stImage[j]->getFrameWidth(),
					_infoList[i].stImage[j]->getFrameHeight());
			}
			for (int j = 0; j < 8; j++)
			{
				_infoList[i].goldImage[j] = IMAGEMANAGER->findImage("goldNum");
				_infoList[i].goldRc[j] = RectMake(_playerList[i].rc.left + 320 + (j *  _infoList[i].goldImage[j]->getFrameWidth()),
					_playerList[i].rc.top + 60,
					_infoList[i].goldImage[j]->getFrameWidth(),
					_infoList[i].goldImage[j]->getFrameHeight());
				if (j < 6)
				{
					_infoList[i].timeIamge[j] = IMAGEMANAGER->findImage("goldNum_w");
					if (j < 2)
						_infoList[i].timeRc[j] = RectMake(_playerList[i].rc.left + 275 + (j *  _infoList[i].timeIamge[j]->getFrameWidth()),
							_playerList[i].rc.top + 95,
							_infoList[i].timeIamge[j]->getFrameWidth(),
							_infoList[i].timeIamge[j]->getFrameHeight());
					if (j >= 2 && j < 4)
						_infoList[i].timeRc[j] = RectMake(_playerList[i].rc.left + 310 + (j *  _infoList[i].timeIamge[j]->getFrameWidth()),
							_playerList[i].rc.top + 95,
							_infoList[i].timeIamge[j]->getFrameWidth(),
							_infoList[i].timeIamge[j]->getFrameHeight());
					if (j >= 4)
						_infoList[i].timeRc[j] = RectMake(_playerList[i].rc.left + 350 + (j *  _infoList[i].timeIamge[j]->getFrameWidth()),
							_playerList[i].rc.top + 95,
							_infoList[i].timeIamge[j]->getFrameWidth(),
							_infoList[i].timeIamge[j]->getFrameHeight());
				}
			}
		}
	}
}

void startScene::showImageInfo()
{
	char str[32];
	int size;
	for (int i = 0; i < MAXPLAYER; i++)
	{
		sprintf_s(str, "%d", _playerList[i].lev);
		size = strlen(str);
		if (size < 2)
		{
			_infoList[i].lvImage[0] = NULL;
			_infoList[i].lvImage[1] = IMAGEMANAGER->findImage("levUpnum");
			_infoList[i].levFrameX[1] = (int)(str[0]) - 46;
		}
		else
		{
			_infoList[i].lvImage[0] = IMAGEMANAGER->findImage("levUpnum");
			_infoList[i].lvImage[1] = IMAGEMANAGER->findImage("levUpnum");
			_infoList[i].levFrameX[0] = (int)(str[0]) - 46;
			_infoList[i].levFrameX[1] = (int)(str[1]) - 46;
		}

		sprintf_s(str, "%d", _playerList[i].star);
		size = strlen(str);
		if (size < 2)
		{
			_infoList[i].stImage[0] = NULL;
			_infoList[i].stImage[1] = IMAGEMANAGER->findImage("levUpnum");
			_infoList[i].stFrameX[1] = (int)(str[0]) - 46;
		}
		else
		{
			_infoList[i].stImage[0] = IMAGEMANAGER->findImage("levUpnum");
			_infoList[i].stImage[1] = IMAGEMANAGER->findImage("levUpnum");
			_infoList[i].stFrameX[0] = (int)(str[0]) - 46;
			_infoList[i].stFrameX[1] = (int)(str[1]) - 46;
		}

		sprintf_s(str, "%d", _playerList[i].gold);
		size = strlen(str);
		for (int j = 0; j < 8; j++)
		{
			if (j < size)
			{
				_infoList[i].goldImage[j] = IMAGEMANAGER->findImage("goldNum");
				_infoList[i].goldFrameX[j] = (int)(str[j]) - 46;
			}
			if(j >= size)
			{
				_infoList[i].goldImage[j] = NULL;
			}
		}

		int hour = _playerList[i].time / 3600;
		int minute = (_playerList[i].time % 3600) / 60;
		int second = (_playerList[i].time % 60);
		sprintf_s(str, "%d", hour);
		size = strlen(str);
		if (size < 2)
		{
			_infoList[i].timeIamge[0] = NULL;
			_infoList[i].timeIamge[1] = IMAGEMANAGER->findImage("goldNum_w");
			_infoList[i].timeFrameX[1] = (int)(str[0]) - 46;
		}
		else
		{
			_infoList[i].timeIamge[0] = IMAGEMANAGER->findImage("goldNum_w");
			_infoList[i].timeIamge[1] = IMAGEMANAGER->findImage("goldNum_w"); 
			_infoList[i].timeFrameX[0] = (int)(str[0]) - 46;
			_infoList[i].timeFrameX[1] = (int)(str[1]) - 46;
		}

		sprintf_s(str, "%d", minute);
		size = strlen(str);
		if (size < 2)
		{
			_infoList[i].timeIamge[2] = NULL;
			_infoList[i].timeIamge[3] = IMAGEMANAGER->findImage("goldNum_w");
			_infoList[i].timeFrameX[3] = (int)(str[0]) - 46;
		}
		else
		{
			_infoList[i].timeIamge[2] = IMAGEMANAGER->findImage("goldNum_w");
			_infoList[i].timeIamge[3] = IMAGEMANAGER->findImage("goldNum_w");
			_infoList[i].timeFrameX[2] = (int)(str[0]) - 46;
			_infoList[i].timeFrameX[3] = (int)(str[1]) - 46;

		}

		sprintf_s(str, "%d", second);
		size = strlen(str);
		if (size < 2)
		{
			_infoList[i].timeIamge[4] = NULL;
			_infoList[i].timeIamge[5] = IMAGEMANAGER->findImage("goldNum_w");
			_infoList[i].timeFrameX[5] = (int)(str[0]) - 46;
		}
		else
		{
			_infoList[i].timeIamge[4] = IMAGEMANAGER->findImage("goldNum_w");
			_infoList[i].timeIamge[5] = IMAGEMANAGER->findImage("goldNum_w");
			_infoList[i].timeFrameX[4] = (int)(str[0]) - 46;
			_infoList[i].timeFrameX[5] = (int)(str[1]) - 46;
		}
	}
}
