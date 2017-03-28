#include "stdafx.h"
#include "soldier.h"


soldier::soldier()
{
}


soldier::~soldier()
{
}

HRESULT soldier::init(const char * charName, POINT position, float speed, int distance, int pow)
{
	sprintf_s(runStr, "%s%s", charName, "Move");
	sprintf_s(attackStr, "%s%s", charName, "Attack");
	sprintf_s(dieStr, "%s%s", charName, "Die");

	if (charName == "Rabbit")
		_arrow = IMAGEMANAGER->findImage("arrow");

	_image = IMAGEMANAGER->findImage(runStr);

	_x = position.x;
	_y = position.y;

	_speed = speed;
	_distance = distance;
	_pow = pow;
	
	if (_speed > 0)
		_offsetX = 300;
	else
		_offsetX = 0;

		_rc = RectMake((int)_x + 30 - _offsetX, (int)_y, _image->getFrameWidth() - 60, _image->getFrameHeight());
	_enemyRc = RectMake((int)_x - _offsetX, (int)_y, _image->getFrameWidth() + _distance, _image->getFrameHeight());
	
	_state = SOLDIER_RUN;
	_progress = new progressBarSoldier;
	_count = _currentFrameX = 0;

	if (charName == "Kzombie")
	{
		_currentHp = _maxHp = 3000 + (DATABASE->getElementData()->nowPlayStage * 100);
		unitKZombie = true;
		_progress->init(_rc.left - 20, _rc.top + 100, 70, 5);
	}
	else
	{
		if(speed > 0)
			_currentHp = _maxHp = 100;
		else
			_currentHp = _maxHp = 100 + (DATABASE->getElementData()->nowPlayStage * 10);
		
		unitKZombie = false;
		_progress->init(_rc.left - 20, _rc.top, 70, 5);
	}

	_arrowCount = 0;
	_arrowFrameX = 0;

	return S_OK;
}

void soldier::release()
{
}

void soldier::update()
{
	frameCount();
	move();

	_enemyRc = RectMake((int)_x - _offsetX, (int)_y, _image->getFrameWidth() + _distance, _image->getFrameHeight());
	_rc = RectMake((int)_x + 30 - _offsetX, (int)_y, _image->getFrameWidth() - 60, _image->getFrameHeight());

	_progress->setX(_rc.left - 20);

	if (unitKZombie)	
		_progress->setY(_rc.top + 100);
	else
		_progress->setY(_rc.top);
	
	_progress->setGauge(_currentHp, _maxHp);
	_progress->update();

	if (_image == IMAGEMANAGER->findImage("RabbitAttack"))
	{
		arrowFrameCount();
	}
}

void soldier::render()
{
	_image->frameRender(getMemDC(), _rc.left - 30 , _rc.top, _currentFrameX, 0);

	if (_image == IMAGEMANAGER->findImage("RabbitAttack"))
	{
		_arrow->frameRender(getMemDC(), _rc.right, (_rc.top + _rc.bottom) / 2 - 20, _arrowFrameX,0);
	}

	_progress->render();
}

void soldier::frameCount()
{
	_count++;
	
	if (_count % 7 == 0)
	{
		_currentFrameX++;

		if (_currentFrameX > _image->getMaxFrameX())
		{
			_currentFrameX = 0;
			_count = 0;
		}
	}
}

void soldier::move()
{
	if (_state == SOLDIER_RUN)
	{
		_image = IMAGEMANAGER->findImage(runStr);
		_x += _speed;
		_rc = RectMake((int)_x + 30, (int)_y, _image->getFrameWidth() - 60, _image->getFrameHeight());
	}
	else if (_state == SOLDIER_ATTACK)
	{
		_image = IMAGEMANAGER->findImage(attackStr);
	}
	else if (_state == SOLDIER_DIE)
	{
		_image = IMAGEMANAGER->findImage(dieStr);
	}
	else
	{
		_image = IMAGEMANAGER->findImage("DethGhost");
	}
}

void soldier::setState(int state)
{
	_state = (SOLDIER_STATE) state;
}

void soldier::arrowFrameCount()
{
	_arrowCount++;

	if (_arrowCount % 7 == 0)
	{
		_arrowFrameX++;

		if (_arrowFrameX > _arrow->getMaxFrameX())
		{
			_arrowFrameX = 0;
			_arrowCount = 0;
		}
	}
}
