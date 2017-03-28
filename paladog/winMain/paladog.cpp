#include "stdafx.h"
#include "paladog.h"


paladog::paladog()
{
}


paladog::~paladog()
{
}

HRESULT paladog::init()
{
	_image = IMAGEMANAGER->findImage("stand_dog");

	_x = 150;
	_y = 130;
	_speed = 2.f;
	_rc = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_isRight = true;


	_maxHp = _hp = DATABASE->getElementData()->maxHp;
	_maxFood = DATABASE->getElementData()->maxFood;
	_maxMp = DATABASE->getElementData()->maxMp;
	_food = _mp = 0;
	_mpCount = 0;
	_foodCount = 0;
	_playerMpCount = DATABASE->getElementData()->mpCount;
	_playerFoodCount = DATABASE->getElementData()->foodCount;

	_going = false;
	_staying = true;
	_demege = 0;

	_hpBar = new progressBarPaladog;
	_hpBar->init(_rc.left + 20, _rc.top - 20, 100, 7);

	_die = false;

	_subMp = 0;
	_offsetX = 0;

	return S_OK;
}

void paladog::release()
{
}

void paladog::update()
{
	keyControl();
	frameCount();
	moveDirection();

	_hpBar->setX(_rc.left + 20);
	_hpBar->setY(_rc.top - 20);
	_hpBar->setGauge(_hp, _maxHp);
	_hpBar->update();

}

void paladog::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	_hpBar->render();

	for (int i = 0; i < _skill.size(); i++)
	{
		if (_skill[i].img == IMAGEMANAGER->findImage("PunchSkill"))
		{
			_skill[i].speed += 4.f;
		}

		_skill[i].rc = RectMake(_skill[i].x + _skill[i].speed - _offsetX, _skill[i].rc.top, _skill[i].img->getFrameWidth(), _skill[i].img->getFrameHeight());
		_skill[i].img->frameRender(getMemDC(), _skill[i].rc.left, _skill[i].rc.top, _skill[i].frameX, 0);

		if (_skill[i].speed > 500 && _skill[i].img == IMAGEMANAGER->findImage("PunchSkill"))
		{
			frameCount(i);
			_skill.erase(_skill.begin() + i);
		}
		else
		{
			frameCount(i);
		}
	}
}

void paladog::keyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_going = true;
		_isRight = false;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_going = false;
		_staying = true;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_going = true;
		_isRight = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_going = false;
		_staying = true;
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_mp >= 38)
		{
			meteoSkill();
		}	
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (_mp >= 10)
		{
			fireSkill();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_mp >= 7)
		{
			punchSkill();
		}
	}
}

void paladog::frameCount()
{
	if (_isRight)
	{
		_currentFrameY = 0;
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
	else
	{
		_currentFrameY = 1;
		_count++;

		if (_count % 7 == 0)
		{
			_currentFrameX--;

			if (_currentFrameX < 0)
			{
				_currentFrameX = _image->getMaxFrameX();
				_count = 0;
			}
		}
	}

	_foodCount++;

	if (_foodCount % _playerFoodCount == 0)
	{
		if (_food < _maxFood)
		{
			_food++;
		}

		_foodCount = 0;
	}

	_mpCount++;

	if (_mpCount % _playerMpCount == 0)
	{
		if (_mp < _maxMp)
		{
			_mp++;
		}

		_mpCount = 0;
	}
}

void paladog::frameCount(int i)
{
	_skill[i].count++;

	if (_skill[i].count % 3 == 0)
	{
		_skill[i].frameX++;

		if (_skill[i].frameX > _skill[i].img->getMaxFrameX())
		{
			_skill[i].frameX = 0;
			_skill[i].count = 0;

			if (_skill[i].img != IMAGEMANAGER->findImage("PunchSkill"))
			{
				_skill.erase(_skill.begin() + i);
			}
		}
	}

}

void paladog::moveDirection()
{
	if (_going)
	{
		_image = IMAGEMANAGER->findImage("run_dog");
		_staying = false;

		if (_isRight)
		{
			_x += _speed;
			_rc = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		}
		else 
		{
			_x -= _speed;
			_rc = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		}

	}
	else if (_staying)
	{
		_going = false;
		_image = IMAGEMANAGER->findImage("stand_dog");
	}

	if (_x < -_image->getFrameWidth() / 2) 
		_x = -_image->getFrameWidth() / 2;
	else if (_x > WINSIZEX - _image->getFrameWidth()) 
		_x = WINSIZEX - _image->getFrameWidth();

	if (_die)
	{
		_image = IMAGEMANAGER->findImage("die_dog");

		if (_currentFrameX == 36)
		{
			SCENEMANAGER->changeScene("DieScene");
		}
	}


}

void paladog::setDie(bool die)
{
	_die = die;
	_isRight = true;
	_x -= 50;
	_y -= 100;

	_rc = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void paladog::meteoSkill()
{
	_subMp = 38;
	_mp -= _subMp;

	skill temp;
	temp.img = IMAGEMANAGER->findImage("MeteoSkill");
	temp.x = _x + 400 + _offsetX;
	temp.y = 50;
	temp.rc = RectMake(_x + 400, temp.y, temp.img->getFrameWidth(), temp.img->getFrameHeight());
	temp.frameX = 0;
	temp.count = 0;
	temp.speed = 0;
	temp.pow = 30;
	_skill.push_back(temp);
}

void paladog::fireSkill()
{
	_subMp = 10;
	_mp -= _subMp;

	skill temp;
	temp.img = IMAGEMANAGER->findImage("FireSkill");
	temp.x = _x + 150 + _offsetX;
	temp.y = _y;
	temp.rc = RectMake(_x + 150, _y, temp.img->getFrameWidth(), temp.img->getFrameHeight());
	temp.frameX = 0;
	temp.count = 0;
	temp.speed = 0;
	temp.pow = 15;
	_skill.push_back(temp);
}

void paladog::punchSkill()
{
	_subMp = 7;
	_mp -= _subMp;

	skill temp;
	temp.img = IMAGEMANAGER->findImage("PunchSkill");
	temp.x = _x + 150 + _offsetX;
	temp.y = _y + 50;
	temp.rc = RectMake(_x + 150, _y + 50, temp.img->getFrameWidth(), temp.img->getFrameHeight());
	temp.frameX = 0;
	temp.count = 0;
	temp.speed = 2.f;
	temp.pow = 10;
	_skill.push_back(temp);
}

