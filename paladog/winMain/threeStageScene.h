#pragma once
#include "gameNode.h"
#include "soldierManager.h"
#include "paladog.h"
#include <vector>
#include "progressBar_N.h"

#define MAXMONSTER 50

struct tagunitslot
{
	image* image;
	RECT rc;
	int unitNum;
	int x, y;
};

struct tagStageClear
{
	image* window;
	image* Star[3];
	image* stageNum[2];
	image* btn;
	image* gold[8];
	RECT rc;
	RECT starRc[3];
	RECT stageRc[2];
	RECT bRc;
	RECT gRc[8];
	int gFrameX[8];
	int bFrameX;
};
class threeStageScene : public gameNode
{
	struct tagPause
	{
		image* window;
		image* resume;
		image* giveUp;
		int rFrameX, gFrameX;
		RECT wRc, rRc, gRc;
	};

	struct numCell
	{
		RECT rc;
		int num;
		image * img;
		int frameX;
	};

	soldierManager* _soldier;
	paladog* _paladog;
	tagStageClear _stageClear;
	int _offsetX;

	// 프레임
	int _currentFrameX, _currentFrameY;
	int _count;
	bool _isRight;

	//게임 일시정지
	RECT _psPause;
	int _psPuaseFrameX;
	bool _puaseClick;
	bool _isPause;
	bool _isStop;

	vector<tagunitslot> _vUnitSlot;
	vector<tagunitslot>::iterator _viUnitSlot;
	progressBar_N* _deathGauge;
	RECT _cRc;

	//Clear
	int _useStar;
	bool _isClear;
	int _gold;
	int _bonusGold;
	bool _stop, _stop2;
	bool _bossAppear;

	tagPause _pause;

	//레벨
	numCell _levelCell;
	int _level;

	//Gold
	numCell _goldCell[5];
	int _getGold;

	float _playTime;

	//몬스터
	int _countEnemy;
	int _countEnemyMax;
	int _minSpeed, _maxSpeed;
	int _monsterNum;

public:
	threeStageScene();
	~threeStageScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
	void slotUpdate();
	void slotMove();
	void stageClear();
	void clearClick();
	void setStar();
	void setDatabase();
	void setGold();
	void enemyCountSpeed();

	void setPause();
	void pauseClick();
	void pauseWindowClick();

	void levelUpdate();
	void goldUpdate();
	void goldLevelRender();
};

