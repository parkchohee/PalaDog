#pragma once

#include "gameNode.h"
#include "progressBarPaladog.h"
#include <vector>

struct skill
{
	RECT rc;

	image* img;
	int x, y;
	float speed;
	int pow;

	int frameX;
	int count;
};

class paladog : public gameNode
{
	vector<skill> _skill;

	image* _image;
	RECT _rc;
	progressBarPaladog* _hpBar;

	float _x, _y;
	float _speed;

	int _maxHp;
	int _maxFood;
	int _maxMp;

	int _hp;
	int _food;
	int _mp;
	int _subMp;

	int _mpCount;		// 회복을 위한 카운트
	int _foodCount;
	int _playerMpCount;	// 플레이어가 회복하는 속도 정해주는 카운트
	int _playerFoodCount;

	int _count;
	int _currentFrameX, _currentFrameY;

	bool _isRight;
	bool _going;
	bool _staying;
	bool _die;

	int _demege;

	int _offsetX;

public:
	paladog();
	~paladog();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
	void frameCount();
	void frameCount(int i);

	void moveDirection();

	RECT getRc() { return _rc; }

	int getHp() { return _hp; }
	int getFood() { return _food; }
	int getMp() { return _mp; }
	int getMaxFood() { return _maxFood; }
	int getMaxMp() { return _maxMp; }
	int getMaxHp() { return _maxHp; }

	void useFood(int food) { _food -= food; }
	void useMp(int mp) { _mp -= mp; }

	void setGoing(bool going) { _going = going; }
	void setRight(bool isRight) { _isRight = isRight; }
	void setStayMode(bool stayMode) { _staying = stayMode; }

	int getX() { return _x; }
	int getY() { return _y; }
	int getSpeed() { return _speed; }

	void setX(float x) { _x = x; }

	bool getGoing() { return _going; }
	bool getRight() { return _isRight; }
	bool getStaying() { return _staying; }
	bool getDie() { return _die; }
	void attack(int attack) { _hp -= attack; }
	void demege(int demege) { _demege = demege; }
	void setDie(bool die);
	int getUseMp() { return _subMp; }

	vector<skill> getSkillVec() { return _skill; }
	void setOffsetX(int offsetX) { _offsetX = offsetX; }

	void meteoSkill();
	void fireSkill();
	void punchSkill();

};

