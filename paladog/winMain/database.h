#pragma once

#include "singletonBase.h"

#include <vector>
#include <map>


class elements
{
public:
	int level;			// 캐릭터 레벨
	int starTotal;		// 총 별 갯수
	int gold;			// 돈
	int playTime;		// 플레이시간
	int currentStage;	// 현재 스테이지
	int stage1;			// 스테이지별 별 갯수 
	int stage2;
	int stage3;
	int stage4;
	int stage5;
	int stage6;
	int stage7;
	int stage8;
	int stage9;
	int stage10;
	int stage11;
	int stage12;

	int mouseLev;
	int mouseHp;
	int mouseAttack;
	int mouseSpeed;
	int mouseDelay;
	float mouseUpgradeAttack;
	int mouseUpgradeHp;
	int mouseUpgradeGold;

	int rabbitLev;
	int rabbitHp;
	int rabbitAttack;
	float rabbitSpeed;
	int rabbitDelay;
	int rabbitUpgradeAttack;
	int rabbitUpgradeHp;
	int rabbitUpgradeGold;

	int bearLev;
	int bearHp;
	int bearAttack;
	float bearSpeed;
	int bearDelay;
	int bearUpgradeAttack;
	int bearUpgradeHp;
	int bearUpgradeGold;

	int kangarooLev;
	int kangarooHp;
	int kangarooAttack;
	float kangarooSpeed;
	int kangarooDelay;
	int kangarooUpgradeAttack;
	int kangarooUpgradeHp;
	int kangarooUpgradeGold;

	// 플레이어 
	int maxHp;		// 팔라독 체력
	int maxMp;		// 마나
	int maxFood;	// 식량
	int mpCount;	// 마나 회복 속도
	int foodCount;	// 식량 회복 속도

	int foodLev;		// 식량 레벨
	int foodCountLev;	// 식량 회복 속도 레벨
	int mpLev;			// 마나 레벨
	int mpCountLev;		// 마나 회복 속도 레벨



	int nowPlayStage; // 시작한 스테이지
	int skillPoint;		// 스킬 포인트

	elements() {}
	~elements() {}
};

class database : public singletonBase<database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;
	const char* _fileName;

	iterElement _mIter;

public:
	database();
	~database();

	HRESULT init();
	HRESULT init(const char* fileName);
	void release();

	void loadDatabase( string name );

	elements* getElementData() { return _mTotalElement.find( _fileName )->second; } 

	void saveDatabase();

	void setLevel(int lev);
	void setStartTotal(int starTotal);
	void setGold(int gold);
	void setPlayTime(int playTime);

	void setCurrentStage(int currentStage);
	void setStageStar1(int star);
	void setStageStar2(int star);
	void setStageStar3(int star);
	void setStageStar4(int star);
	void setStageStar5(int star);
	void setStageStar6(int star);
	void setStageStar7(int star);
	void setStageStar8(int star);
	void setStageStar9(int star);
	void setStageStar10(int star);
	void setStageStar11(int star);
	void setStageStar12(int star);

	void setMouseLev(int lev);
	void setMouseHp(int hp);
	void setMouseAttack(int attack);
	void setMouseSpeed(float speed);
	void setMouseDelay(int delay);
	void setMouseUpgradeAttack(int attack);
	void setMouseUpgradeHp(int hp);
	void setMouseUpgradeGold(int gold);
	
	void setRabbitLev(int lev);
	void setRabbitHp(int hp);
	void setRabbitAttack(int attack);
	void setRabbitSpeed(float speed);
	void setRabbitDelay(int delay);
	void setRabbitUpgradeAttack(int attack);
	void setRabbitUpgradeHp(int hp);
	void setRabbitUpgradeGold(int gold);

	void setBearLev(int lev);
	void setBearHp(int hp);
	void setBearAttack(int attack);
	void setBearSpeed(float speed);
	void setBearDelay(int delay);
	void setBearUpgradeAttack(int attack);
	void setBearUpgradeHp(int hp);
	void setBearUpgradeGold(int gold);

	void setKangarooLev(int lev);
	void setKangarooHp(int hp);
	void setKangarooAttack(int attack);
	void setKangarooSpeed(float speed);
	void setKangarooDelay(int delay);
	void setKangarooUpgradeAttack(int attack);
	void setKangarooUpgradeHp(int hp);
	void setKangarooUpgradeGold(int gold);

	void setMaxHp(int hp);
	void setMaxMp(int mp);
	void setMaxFood(int food);
	void setMpCount(int mpCount);
	void setFoodCount(int foodCount);
	void setFoodLev(int lev);
	void setFoodCountLev(int lev);
	void setMpLev(int lev);
	void setMpCountLev(int lev);


	void setNowPlayStage(int stage);
	void setSkillPoint(int point);
};

