#include "stdafx.h"
#include "progressBarSoldier.h"


progressBarSoldier::progressBarSoldier()
{
}


progressBarSoldier::~progressBarSoldier()
{
}

HRESULT progressBarSoldier::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarForward = IMAGEMANAGER->addImage("barForward2", "image/hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage("barBack2", "image/hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarForward->getWidth();

	return S_OK;
}

void progressBarSoldier::release()
{
}

void progressBarSoldier::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarBack->getWidth(), _progressBarForward->getHeight());

}

void progressBarSoldier::render()
{
	IMAGEMANAGER->render("barBack2", getMemDC(),
		_rcProgress.left + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		0, 0,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	IMAGEMANAGER->render("barForward2", getMemDC(),
		_rcProgress.left + _progressBarForward->getWidth() / 2,
		_y + _progressBarForward->getHeight() / 2,
		0, 0,
		_width, _progressBarForward->getHeight());
}

void progressBarSoldier::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}
