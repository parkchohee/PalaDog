#pragma once

#include "gameNode.h"
#include "soldier.h"
#include <vector>

class paladog;

class soldierManager : public gameNode
{
	RECT _rc;
	RECT _rcAttack;

	vector<soldier*> _vSoldier;
	vector<soldier*>::iterator _viSoldier;

	vector<soldier*> _vEnemy;
	vector<soldier*>::iterator _viEnemy;

	paladog* _paladog;

	int _deathCount;

	int _offsetX;

	int _bossHp;
	int _unitGold;
	bool kingDie;

	//kingZombieInfo
	int _kingX;
	bool _attack;

public:
	soldierManager();
	~soldierManager();

	HRESULT init(RECT rc = { NULL }, RECT rcAttack = { NULL });
	void release();
	void update();
	void render();

	void createSoldier(const char* charName, POINT position, float speed, int distance, int pow);
	void collision();

	void setPaladogMemoryLink(paladog* paladog) { _paladog = paladog; }
	int getDeathCount() { return _deathCount; }
	
	void setOffsetX(int x) { _offsetX = x; }

	void setRc(RECT rc) { _rc = rc; }
	void setAttackRc(RECT rc) { _rcAttack = rc; }

	void setBossHp(int hp) { _bossHp = hp; }
	int getBossHp() { return _bossHp; }

	int getGold() { return _unitGold; }
	void setGold() { _unitGold = 0; }

	bool getKingDie() { return kingDie; }

	int getkingX() { return _kingX; }
	bool getKAttack() { return _attack; }
	void setKAttack(bool attack) { _attack = attack; }

};

