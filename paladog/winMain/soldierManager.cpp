#include "stdafx.h"
#include "soldierManager.h"
#include "paladog.h"


soldierManager::soldierManager()
{
}


soldierManager::~soldierManager()
{
}

HRESULT soldierManager::init(RECT rc, RECT rcAttack)
{
	_rc = rc;
	_rcAttack = rcAttack;
	kingDie = false;

	return S_OK;
}

void soldierManager::release()
{
	for (int i = 0; i < _vSoldier.size(); i++)
	{
		_vSoldier[i]->release();
		SAFE_DELETE(_vSoldier[i]);
	}

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->release();
		SAFE_DELETE(_vEnemy[i]);
	}
}

void soldierManager::update()
{
	for (_viSoldier = _vSoldier.begin(); _viSoldier != _vSoldier.end(); ++_viSoldier)
	{
		RECT temp;

		if (IntersectRect(&temp, &(*_viSoldier)->getRect(), &_rc))
		{
			(*_viSoldier)->setSpeed(0.f);
		}

		if (IntersectRect(&temp, &(*_viSoldier)->getRect(), &_rcAttack))
		{
			if ((*_viSoldier)->getState() != 2 && (*_viSoldier)->getState() != 3)
			{
				(*_viSoldier)->setState(1);
			
				if ((*_viSoldier)->getCurrentFrameX() == 1 && (*_viSoldier)->getCount() == 8)
					_bossHp -= (*_viSoldier)->getPow();
				
			}
		}

		(*_viSoldier)->update();
		(*_viSoldier)->setOffsetX(_offsetX);	
	}

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
		(*_viEnemy)->setOffsetX(_offsetX);	
	}

	collision();
}

void soldierManager::render()
{
	for (_viSoldier = _vSoldier.begin(); _viSoldier != _vSoldier.end(); ++_viSoldier)
	{
		(*_viSoldier)->render();
	}

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

}

void soldierManager::createSoldier(const char* charName, POINT position, float speed, int distance, int pow)
{
	soldier* tempSoldier = new soldier;
	tempSoldier->init(charName, position, speed, distance, pow);

	if (speed < 0)
	{
		_vEnemy.push_back(tempSoldier);		
		collision();
	}
	else
	{
		_vSoldier.push_back(tempSoldier);
		collision();
	}
}

void soldierManager::collision()
{
	for (int i = 0; i < _paladog->getSkillVec().size(); i++)
	{
		for (int j = 0; j < _vEnemy.size(); j++)
		{
			if (_vEnemy[j]->getState() == 2 || _vEnemy[j]->getState() == 3) continue;

			if (IntersectRect(&RectMake(0, 0, 0, 0), &_paladog->getSkillVec()[i].rc, &_vEnemy[j]->getEnemyRect()))
			{
				if (_vEnemy[j]->getCurrentFrameX() == 1 && _vEnemy[j]->getCount() == 8)
				{
					_vEnemy[j]->attack(_paladog->getSkillVec()[i].pow);

					if (_vEnemy[j]->getCurrentHp() < 0)
					{
						_vEnemy[j]->setState(2);

						if (_vEnemy[j]->getKzombie())	
							_unitGold = RND->getFromIntTo(100, 500);
						else      
							_unitGold = RND->getFromIntTo(10, 20);
					}
				}

			}
		}

		if (IntersectRect(&RectMake(0,0,0,0), &_paladog->getSkillVec()[i].rc, &_rcAttack))
		{
			if (_paladog->getSkillVec()[i].count == 2 && _paladog->getSkillVec()[i].frameX == 0)
			{
				_bossHp -= _paladog->getSkillVec()[i].pow;
			}
		}
	}

	for (int j = 0; j < _vEnemy.size(); j++)
	{
		if (_vEnemy[j]->getState() == 2 &&
			_vEnemy[j]->getCurrentFrameX() == _vEnemy[j]->getMaxFrameX())
		{
			_vEnemy[j]->setState(3);
			_vEnemy[j]->setFrameX(0);
			break;
		}

		if (_vEnemy[j]->getState() == 3 &&
			_vEnemy[j]->getCurrentFrameX() == _vEnemy[j]->getMaxFrameX())
		{
			if (_vEnemy[j]->getKzombie())
				_unitGold = RND->getFromIntTo(100, 500);
			else  
				_unitGold = RND->getFromIntTo(10, 20);
		
			_vEnemy.erase(_vEnemy.begin() + j);				// 여기에러 순서 바꿔야댐
			_deathCount += 1;

			break;
		}
	}

	// soldier 기준으로 enemy와 충돌체크
	for (int i = 0; i < _vSoldier.size(); i++)
	{
		if (_vSoldier[i]->getState() == 2 || _vSoldier[i]->getState() == 3) continue;

		for (int j = 0; j < _vEnemy.size(); j++)
		{
			if (_vEnemy[j]->getState() == 2 || _vEnemy[j]->getState() == 3) continue;
			
			// soldier의 적감지 렉트에 적이 들어오면
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_vSoldier[i]->getEnemyRect(), &_vEnemy[j]->getEnemyRect()))
			{
				// soldier의 이미지를 공격 이미지로 변경한다...
				_vSoldier[i]->setState(1); 
				if (_vEnemy[j]->getKzombie() && _vEnemy[j]->getCurrentFrameX() == 15 && _vEnemy[j]->getCount() == 106)
				{
					_kingX = _vEnemy[j]->getX();
					_attack = true;
				}

				// soldier의 프레임이 1번이고 카운트가 8일때 적에게 soldier의 pow만큼 공격...
				if (_vSoldier[i]->getCurrentFrameX() == 1 && _vSoldier[i]->getCount() == 8)
				{					
					_vEnemy[j]->attack(_vSoldier[i]->getPow());
				}

				// 만약 적의 hp가 0보다 적어지면....
				if (_vEnemy[j]->getCurrentHp() < 0)
				{
					// 죽는다!
					_vEnemy[j]->setState(2);
					_vEnemy[j]->setFrameX(0);
				
					if (_vEnemy[j]->getKzombie())
					{
						kingDie = true;
					}
				}

				break;
			}
			else
			{
				_vSoldier[i]->setState(0);
			}
		}

	}

	// enemy 기준으로 soldier와 충돌체크
	for (int j = 0; j < _vEnemy.size(); j++)
	{
		if (_vEnemy[j]->getState() == 2 || _vEnemy[j]->getState() == 3) continue;

		for (int i = 0; i < _vSoldier.size(); i++)
		{		
			if ( _vSoldier[i]->getState() == 2 &&
				 _vSoldier[i]->getCurrentFrameX() == _vSoldier[i]->getMaxFrameX())
			{
				 _vSoldier[i]->setState(3);
				 _vSoldier[i]->setFrameX(0);

				break;
			}

			if ( _vSoldier[i]->getState() == 3 &&
				 _vSoldier[i]->getCurrentFrameX() == _vSoldier[i]->getMaxFrameX())
			{
				_vSoldier.erase(_vSoldier.begin() + i);

				break;
			}

			if (_vSoldier[i]->getState() == 2 || _vSoldier[i]->getState() == 3) continue;

			if (IntersectRect(&RectMake(0, 0, 0, 0), &_vSoldier[i]->getRect(), &_vEnemy[j]->getEnemyRect()))
			{
				_vEnemy[j]->setState(1);
				
				if (_vEnemy[j]->getCurrentFrameX() == 1 && _vEnemy[j]->getCount() == 8)
					_vSoldier[i]->attack(_vEnemy[j]->getPow());

				if (_vSoldier[i]->getCurrentHp() < 0)
				{
					// 죽는모션 넣어야하는데...
					_vSoldier[i]->setState(2);
					_vSoldier[i]->setFrameX(0);
					//_vSoldier.erase(_vSoldier.begin() + i);
				}

				break;
			}
			else
			{
				_vEnemy[j]->setState(0);
			}

		}

	}
	
	// paladog과 enemy 
	if (!_paladog->getDie())
	{
		for (int j = 0; j < _vEnemy.size(); j++)
		{
			if (_vEnemy[j]->getState() == 2 || _vEnemy[j]->getState() == 3) continue;

			if (IntersectRect(&RectMake(0, 0, 0, 0), &_paladog->getRc(), &_vEnemy[j]->getEnemyRect()))
			{
				if (_vEnemy[j]->getCurrentFrameX() == 1 && _vEnemy[j]->getCount() == 8)
				{
					_paladog->attack(_vEnemy[j]->getPow());

					if (_paladog->getHp() < 0)
					{
						_paladog->setDie(true);
					}
				}

				_vEnemy[j]->setState(1);
			}
		}
	}

	if (_vSoldier.size() == 0)
	{
		for (int i = 0; i < _vEnemy.size(); i++)
		{
			if (_vEnemy[i]->getState() == 2 || _vEnemy[i]->getState() == 3) continue;

			if (IntersectRect(&RectMake(0, 0, 0, 0), &_paladog->getRc(), &_vEnemy[i]->getEnemyRect()))
			{
				_vEnemy[i]->setState(1);
			}
			else
			{
				_vEnemy[i]->setState(0);
			}
		}
	}

	if (_vEnemy.size() == 0)
	{
		for (int i = 0; i < _vSoldier.size(); i++)
		{
			_vSoldier[i]->setState(0);
		}
	}

}
