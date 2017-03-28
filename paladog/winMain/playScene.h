#pragma once

#include "gameNode.h"
#include "soldierManager.h"
#include "paladog.h"


#define GAUGEMAX 254

enum bossState
{
	BOSS_NORMAL,
	BOSS_WEAK,
	BOSS_DIE
};

struct soldierSlot
{
	image* img;
	RECT rc;

	int frameX;

	bool delay;
	int delayCount;
	int delayMaxCount;

	int food;
};

struct skillSlot
{
	image* img;
	RECT rc;

	int frameX;
	int skill;
};

struct guageCell
{
	RECT rc;
	image * img;

	float size;
	bool being;
};

struct numCell
{
	RECT rc;
	image * img;

	int num;
	int frameX;
};

struct boss
{
	RECT rc;
	bossState state;

	image * img;
	image * imgUp;

	int x, y;
	int power;
};

struct tagClear
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

class playScene : public gameNode
{
	struct tagPause
	{
		image* window;
		image* resume;
		image* giveUp;
		int rFrameX, gFrameX;
		RECT wRc, rRc, gRc;
	};

	soldierManager* _soldier;
	paladog* _paladog;

	soldierSlot _soldierSlot[9];

	// 배경
	image * _map;
	int _offsetX;
	int _maxOffsetX;

	// 프레임
	int _currentFrameX, _currentFrameY;
	int _count;
	bool _isRight;

	//게임 일시정지
	RECT _psPause;
	bool _isPause;

	//food, mp용
	float _foodMaxGauge;
	float _mpMaxGauge;
	int _foodGauge;
	int _mpGauge;
	int _subFood;
	int _subMp;
	guageCell _psFood[GAUGEMAX];
	guageCell _psMp[GAUGEMAX];

	numCell _psFoodNumMax[4];
	numCell _psFoodNum[4];

	numCell _psMpNumMax[4];
	numCell _psMpNum[4];


	//left, right 버튼
	RECT _leftBtnRc;
	RECT _rightBtnRc;
	int _leftBtnFrameX;
	int _rightBtnFrameX;

	//hp용
	RECT _paladogTotal;
	RECT _paladogCurrent;
	int _palaHpWidth;

	RECT _bossTotal;
	RECT _bossCurrent;
	int _bossHpWidth;

	int _palaTotalhp;
	int _palaCurrentHp;
	float _palaHpRatio;

	int _bossTotalhp;
	int _bossCurrentHp;
	int _bossDemage;
	float _bossHpRatio;

	int _currentGaugeWidth;

	//보스
	boss _boss;
	
	//레벨
	numCell _levelCell;
	int _level;

	//Gold
	numCell _goldCell[5];
	int _gold;
	int _getGold;

	//skill
	skillSlot _skill[3];

	//Clear
	tagClear _stageClear;
	int _useStar;
	bool _isClear;
	//int _gold;
	int _bonusGold;

	tagPause _pause;

	float _playTime;
	//몬스터
	int _countEnemy;
	int _countEnemyMax;
	int _minSpeed, _maxSpeed;
	int _monsterNum;


public:
	playScene();
	~playScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();

	void slotUpdate();

	void foodMpUpdate();
	void foodMpRender();

	void btnUpClickLR();

	void hpSetting();
	void hpRender();

	void backgroundLoop();
	void bossLoop();
	void bossSetting();

	void levelUpdate();
	void goldUpdate();
	void goldLevelRender();

	void skillUpdate();

	void btnClickSodier();
	void btnClickSkill();


	void stageClear();
	void clearClick();
	void setStar();

	void setPause();
	void pauseClick();
	void pauseWindowClick();



	void setGold();
	void setDatabase();
};

