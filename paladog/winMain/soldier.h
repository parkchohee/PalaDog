#pragma once

#include "gameNode.h"
#include "progressBarSoldier.h"

enum SOLDIER_STATE
{
	SOLDIER_RUN,
	SOLDIER_ATTACK,
	SOLDIER_DIE,
	SOLDIER_GHOST
};

class soldier : public gameNode
{
	image* _image;

	char runStr[32];
	char attackStr[32];
	char dieStr[32];

	RECT _rc;
	float _x, _y;
	float _speed;
	int _pow;

	// 상태
	SOLDIER_STATE _state;

	// 적감지 렉트
	RECT _enemyRc;
	int _distance;

	// 프레임
	int _count;
	int _currentFrameX;

	// HP
	int _maxHp;
	int _currentHp;

	// 프로그레스바
	progressBarSoldier* _progress;








	RECT _rcProgress;
	int _progressX, _progressY;
	float _progressWidth;

	image* _progressBarForward;
	image* _progressBarBack;









	int _offsetX;
	//킹좀비냐
	bool unitKZombie;

	image* _arrow;
	int _arrowCount;
	int _arrowFrameX;

public:
	soldier();
	~soldier();

	HRESULT init(const char* charName, POINT position, float speed, int distance, int pow);
	void release();
	void update();
	void render();

	void frameCount();
	void move();

	RECT getEnemyRect() { return _enemyRc; }
	RECT getRect() { return _rc; }
	void setState(int state);
	int getState() { return (int)_state; }

	int getPow() { return _pow; }

	int getCurrentHp() { return _currentHp; }
	int getCurrentFrameX() { return _currentFrameX; }
	int getCount() { return _count; }
	void attack(int pow) { _currentHp -= pow; }

	void setFrameX(int x) { _currentFrameX = x; }
	int getMaxFrameX() { return _image->getMaxFrameX(); }

	void setSpeed(float speed) { _speed = speed; }
	void setOffsetX(int x) { _offsetX = x; }

	bool getKzombie() { return unitKZombie; }

	void arrowFrameCount();

	float getX() { return _x; }
};

