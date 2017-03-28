#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{
}

HRESULT database::init()
{
	return S_OK;
}

HRESULT database::init(const char * fileName)
{
	_fileName = fileName;
	loadDatabase(fileName);

	return S_OK;
}

void database::release()
{
	iterElement mIter = _mTotalElement.begin();

	for ( ; mIter != _mTotalElement.end(); )
	{
		if ( mIter->second )
		{
			SAFE_DELETE( mIter->second );
			mIter = _mTotalElement.erase( mIter );
		}
		else
			++mIter;
	}

	_mTotalElement.clear();
}

void database::loadDatabase( string name )
{
	//데이터를 읽어오자
	arrElements vTemp;
	vTemp = TXTDATA->txtLoad( name.c_str() );

	string str;
	int count = 0;

	elements* em = new elements;
	_mTotalElement.insert(pair<string, elements*>(name, em));

	_mIter = _mTotalElement.find(name);

	_mIter->second->level = atoi(vTemp[0].c_str());
	_mIter->second->starTotal = atoi(vTemp[1].c_str());
	_mIter->second->gold = atoi(vTemp[2].c_str());
	_mIter->second->playTime = atoi(vTemp[3].c_str());
	_mIter->second->currentStage = atoi(vTemp[4].c_str());
	_mIter->second->stage1 = atoi(vTemp[5].c_str());
	_mIter->second->stage2 = atoi(vTemp[6].c_str());
	_mIter->second->stage3 = atoi(vTemp[7].c_str());
	_mIter->second->stage4 = atoi(vTemp[8].c_str());
	_mIter->second->stage5 = atoi(vTemp[9].c_str());
	_mIter->second->stage6 = atoi(vTemp[10].c_str());
	_mIter->second->stage7 = atoi(vTemp[11].c_str());
	_mIter->second->stage8 = atoi(vTemp[12].c_str());
	_mIter->second->stage9 = atoi(vTemp[13].c_str());
	_mIter->second->stage10 = atoi(vTemp[14].c_str());
	_mIter->second->stage11 = atoi(vTemp[15].c_str());
	_mIter->second->stage12 = atoi(vTemp[16].c_str());
	
	_mIter->second->mouseLev = atoi(vTemp[17].c_str());
	_mIter->second->mouseHp = atoi(vTemp[18].c_str());
	_mIter->second->mouseAttack = atoi(vTemp[19].c_str());
	_mIter->second->mouseSpeed = atof(vTemp[20].c_str());
	_mIter->second->mouseDelay = atoi(vTemp[21].c_str());
	_mIter->second->mouseUpgradeAttack = atoi(vTemp[22].c_str());
	_mIter->second->mouseUpgradeHp = atoi(vTemp[23].c_str());
	_mIter->second->mouseUpgradeGold = atoi(vTemp[24].c_str());
	
	_mIter->second->rabbitLev = atoi(vTemp[25].c_str());
	_mIter->second->rabbitHp = atoi(vTemp[26].c_str());
	_mIter->second->rabbitAttack = atoi(vTemp[27].c_str());
	_mIter->second->rabbitSpeed = atof(vTemp[28].c_str());
	_mIter->second->rabbitDelay = atoi(vTemp[29].c_str());
	_mIter->second->rabbitUpgradeAttack = atoi(vTemp[30].c_str());
	_mIter->second->rabbitUpgradeHp = atoi(vTemp[31].c_str());
	_mIter->second->rabbitUpgradeGold = atoi(vTemp[32].c_str());
	
	_mIter->second->bearLev = atoi(vTemp[33].c_str());
	_mIter->second->bearHp = atoi(vTemp[34].c_str());
	_mIter->second->bearAttack = atoi(vTemp[35].c_str());
	_mIter->second->bearSpeed = atof(vTemp[36].c_str());
	_mIter->second->bearDelay = atoi(vTemp[37].c_str());
	_mIter->second->bearUpgradeAttack = atoi(vTemp[38].c_str());
	_mIter->second->bearUpgradeHp = atoi(vTemp[39].c_str());
	_mIter->second->bearUpgradeGold = atoi(vTemp[40].c_str());
	
	_mIter->second->kangarooLev = atoi(vTemp[41].c_str());
	_mIter->second->kangarooHp = atoi(vTemp[42].c_str());
	_mIter->second->kangarooAttack = atoi(vTemp[43].c_str());
	_mIter->second->kangarooSpeed = atof(vTemp[44].c_str());
	_mIter->second->kangarooDelay = atoi(vTemp[45].c_str());
	_mIter->second->kangarooUpgradeAttack = atoi(vTemp[46].c_str());
	_mIter->second->kangarooUpgradeHp = atoi(vTemp[47].c_str());
	_mIter->second->kangarooUpgradeGold = atoi(vTemp[48].c_str());

	// 플레이어정보
	_mIter->second->maxHp = atoi(vTemp[49].c_str());
	_mIter->second->maxMp = atoi(vTemp[50].c_str());
	_mIter->second->maxFood = atoi(vTemp[51].c_str());
	_mIter->second->mpCount = atoi(vTemp[52].c_str());
	_mIter->second->foodCount = atoi(vTemp[53].c_str());

	_mIter->second->foodLev = atoi(vTemp[54].c_str());
	_mIter->second->foodCountLev = atoi(vTemp[55].c_str());
	_mIter->second->mpLev = atoi(vTemp[56].c_str());
	_mIter->second->mpCountLev = atoi(vTemp[57].c_str());


	// 현재스테이지 저장
	_mIter->second->nowPlayStage = atoi(vTemp[58].c_str());

	// 스킬 포인트
	_mIter->second->skillPoint = atoi(vTemp[59].c_str());

	vTemp.clear();
}

void database::saveDatabase()
{
	int totalStar = this->getElementData()->stage1 +
		this->getElementData()->stage2 +
		this->getElementData()->stage3 +
		this->getElementData()->stage4 +
		this->getElementData()->stage5 +
		this->getElementData()->stage6 +
		this->getElementData()->stage7 +
		this->getElementData()->stage8 +
		this->getElementData()->stage9 +
		this->getElementData()->stage10 +
		this->getElementData()->stage11 +
		this->getElementData()->stage12;

	vector<string> vStr;
	// 레벨, 별, 돈, 플레이시간, 현재클리어스테이지, 스테이지1~12 별갯수 
	//vStr.push_back("1, 0, 20000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0");
	vStr.push_back(to_string(this->getElementData()->level));
	vStr.push_back(to_string(totalStar));
	vStr.push_back(to_string(this->getElementData()->gold));
	vStr.push_back(to_string(this->getElementData()->playTime));
	vStr.push_back(to_string(this->getElementData()->currentStage));
	vStr.push_back(to_string(this->getElementData()->stage1));
	vStr.push_back(to_string(this->getElementData()->stage2));
	vStr.push_back(to_string(this->getElementData()->stage3));
	vStr.push_back(to_string(this->getElementData()->stage4));
	vStr.push_back(to_string(this->getElementData()->stage5));
	vStr.push_back(to_string(this->getElementData()->stage6));
	vStr.push_back(to_string(this->getElementData()->stage7));
	vStr.push_back(to_string(this->getElementData()->stage8));
	vStr.push_back(to_string(this->getElementData()->stage9));
	vStr.push_back(to_string(this->getElementData()->stage10));
	vStr.push_back(to_string(this->getElementData()->stage11));
	vStr.push_back(to_string(this->getElementData()->stage12));

	// 쥐 정보
	vStr.push_back(to_string(this->getElementData()->mouseLev));
	vStr.push_back(to_string(this->getElementData()->mouseHp));
	vStr.push_back(to_string(this->getElementData()->mouseAttack));
	vStr.push_back(to_string(this->getElementData()->mouseSpeed));
	vStr.push_back(to_string(this->getElementData()->mouseDelay));
	vStr.push_back(to_string(this->getElementData()->mouseUpgradeAttack));
	vStr.push_back(to_string(this->getElementData()->mouseUpgradeHp));
	vStr.push_back(to_string(this->getElementData()->mouseUpgradeGold));
	
	// 토끼 정보
	vStr.push_back(to_string(this->getElementData()->rabbitLev));
	vStr.push_back(to_string(this->getElementData()->rabbitHp));
	vStr.push_back(to_string(this->getElementData()->rabbitAttack));
	vStr.push_back(to_string(this->getElementData()->rabbitSpeed));
	vStr.push_back(to_string(this->getElementData()->rabbitDelay));
	vStr.push_back(to_string(this->getElementData()->rabbitUpgradeAttack));
	vStr.push_back(to_string(this->getElementData()->rabbitUpgradeHp));
	vStr.push_back(to_string(this->getElementData()->rabbitUpgradeGold));

	// 곰 정보
	vStr.push_back(to_string(this->getElementData()->bearLev));
	vStr.push_back(to_string(this->getElementData()->bearHp));
	vStr.push_back(to_string(this->getElementData()->bearAttack));
	vStr.push_back(to_string(this->getElementData()->bearSpeed));
	vStr.push_back(to_string(this->getElementData()->bearDelay));
	vStr.push_back(to_string(this->getElementData()->bearUpgradeAttack));
	vStr.push_back(to_string(this->getElementData()->bearUpgradeHp));
	vStr.push_back(to_string(this->getElementData()->bearUpgradeGold));
	
	// 캥거루 정보
	vStr.push_back(to_string(this->getElementData()->kangarooLev));
	vStr.push_back(to_string(this->getElementData()->kangarooHp));
	vStr.push_back(to_string(this->getElementData()->kangarooAttack));
	vStr.push_back(to_string(this->getElementData()->kangarooSpeed));
	vStr.push_back(to_string(this->getElementData()->kangarooDelay));
	vStr.push_back(to_string(this->getElementData()->kangarooUpgradeAttack));
	vStr.push_back(to_string(this->getElementData()->kangarooUpgradeHp));
	vStr.push_back(to_string(this->getElementData()->kangarooUpgradeGold));

	// 플레이어
	vStr.push_back(to_string(this->getElementData()->maxHp));
	vStr.push_back(to_string(this->getElementData()->maxMp));
	vStr.push_back(to_string(this->getElementData()->maxFood));
	vStr.push_back(to_string(this->getElementData()->mpCount));
	vStr.push_back(to_string(this->getElementData()->foodCount));

	vStr.push_back(to_string(this->getElementData()->foodLev));
	vStr.push_back(to_string(this->getElementData()->foodCountLev));
	vStr.push_back(to_string(this->getElementData()->mpLev));
	vStr.push_back(to_string(this->getElementData()->mpCountLev));

	vStr.push_back(to_string(this->getElementData()->nowPlayStage));
	vStr.push_back(to_string(this->getElementData()->skillPoint));

	TXTDATA->txtSave(_fileName, vStr);
}

void database::setLevel(int lev)
{
	_mIter->second->level = lev;
}

void database::setStartTotal(int starTotal)
{
	_mIter->second->starTotal = starTotal;
}

void database::setGold(int gold)
{
	_mIter->second->gold = gold;
}

void database::setPlayTime(int playTime)
{
	_mIter->second->playTime = playTime;
}

void database::setCurrentStage(int currentStage)
{
	_mIter->second->currentStage = currentStage;
}

void database::setStageStar1(int star)
{
	_mIter->second->stage1 = star;
}

void database::setStageStar2(int star)
{
	_mIter->second->stage2 = star;
}

void database::setStageStar3(int star)
{
	_mIter->second->stage3 = star;
}

void database::setStageStar4(int star)
{
	_mIter->second->stage4 = star;
}

void database::setStageStar5(int star)
{
	_mIter->second->stage5 = star;
}

void database::setStageStar6(int star)
{
	_mIter->second->stage6 = star;
}

void database::setStageStar7(int star)
{
	_mIter->second->stage7 = star;
}

void database::setStageStar8(int star)
{
	_mIter->second->stage8 = star;
}

void database::setStageStar9(int star)
{
	_mIter->second->stage9 = star;
}

void database::setStageStar10(int star)
{
	_mIter->second->stage10 = star;
}

void database::setStageStar11(int star)
{
	_mIter->second->stage11 = star;
}

void database::setStageStar12(int star)
{
	_mIter->second->stage12 = star;
}

void database::setMouseLev(int lev)
{
	_mIter->second->mouseLev = lev;
}

void database::setMouseHp(int hp)
{
	_mIter->second->mouseHp = hp;
}

void database::setMouseAttack(int attack)
{
	_mIter->second->mouseAttack = attack;
}

void database::setMouseSpeed(float speed)
{
	_mIter->second->mouseSpeed = speed;
}

void database::setMouseDelay(int delay)
{
	_mIter->second->mouseDelay = delay;
}

void database::setMouseUpgradeAttack(int attack)
{
	_mIter->second->mouseUpgradeAttack = attack;
}

void database::setMouseUpgradeHp(int hp)
{
	_mIter->second->mouseUpgradeHp = hp;
}

void database::setMouseUpgradeGold(int gold)
{
	_mIter->second->mouseUpgradeGold = gold;
}

void database::setRabbitLev(int lev)
{
	_mIter->second->rabbitLev = lev;
}

void database::setRabbitHp(int hp)
{
	_mIter->second->rabbitHp = hp;
}

void database::setRabbitAttack(int attack)
{
	_mIter->second->rabbitAttack = attack;
}

void database::setRabbitSpeed(float speed)
{
	_mIter->second->rabbitSpeed = speed;
}

void database::setRabbitDelay(int delay)
{
	_mIter->second->rabbitDelay = delay;
}

void database::setRabbitUpgradeAttack(int attack)
{
	_mIter->second->rabbitUpgradeAttack = attack;
}

void database::setRabbitUpgradeHp(int hp)
{
	_mIter->second->rabbitUpgradeHp = hp;
}

void database::setRabbitUpgradeGold(int gold)
{
	_mIter->second->rabbitUpgradeGold = gold;
}

void database::setBearLev(int lev)
{
	_mIter->second->bearLev = lev;
}

void database::setBearHp(int hp)
{
	_mIter->second->bearHp = hp;
}

void database::setBearAttack(int attack)
{
	_mIter->second->bearAttack = attack;
}

void database::setBearSpeed(float speed)
{
	_mIter->second->bearSpeed = speed;
}

void database::setBearDelay(int delay)
{
	_mIter->second->bearDelay = delay;
}

void database::setBearUpgradeAttack(int attack)
{
	_mIter->second->bearUpgradeAttack = attack;
}

void database::setBearUpgradeHp(int hp)
{
	_mIter->second->bearUpgradeHp = hp;
}

void database::setBearUpgradeGold(int gold)
{
	_mIter->second->bearUpgradeGold = gold;
}

void database::setKangarooLev(int lev)
{
	_mIter->second->kangarooLev = lev;
}

void database::setKangarooHp(int hp)
{
	_mIter->second->kangarooHp = hp;
}

void database::setKangarooAttack(int attack)
{
	_mIter->second->kangarooAttack = attack;
}

void database::setKangarooSpeed(float speed)
{
	_mIter->second->kangarooSpeed = speed;
}

void database::setKangarooDelay(int delay)
{
	_mIter->second->kangarooDelay = delay;
}

void database::setKangarooUpgradeAttack(int attack)
{
	_mIter->second->kangarooUpgradeAttack = attack;
}

void database::setKangarooUpgradeHp(int hp)
{
	_mIter->second->kangarooUpgradeHp = hp;
}

void database::setKangarooUpgradeGold(int gold)
{
	_mIter->second->kangarooUpgradeGold = gold;
}

void database::setMaxHp(int hp)
{
	_mIter->second->maxHp = hp;
}

void database::setMaxMp(int mp)
{
	_mIter->second->maxMp = mp;
}

void database::setMaxFood(int food)
{
	_mIter->second->maxFood = food;
}

void database::setMpCount(int mpCount)
{
	_mIter->second->mpCount = mpCount;
}

void database::setFoodCount(int foodCount)
{
	_mIter->second->foodCount = foodCount;
}

void database::setFoodLev(int lev)
{
	_mIter->second->foodLev = lev;
}

void database::setFoodCountLev(int lev)
{
	_mIter->second->foodCountLev = lev;
}

void database::setMpLev(int lev)
{
	_mIter->second->mpLev = lev;
}

void database::setMpCountLev(int lev)
{
	_mIter->second->mpCountLev = lev;
}

void database::setNowPlayStage(int stage)
{
	_mIter->second->nowPlayStage = stage;
}

void database::setSkillPoint(int point)
{
	_mIter->second->skillPoint = point;
}
