#include "stdafx.h"
#include "progressBarPaladog.h"


progressBarPaladog::progressBarPaladog()
{
}


progressBarPaladog::~progressBarPaladog()
{
}

HRESULT progressBarPaladog::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarForward = IMAGEMANAGER->addImage("barForward3", "image/hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage("barBack3", "image/hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarForward->getWidth();

	return S_OK;
}

void progressBarPaladog::release()
{
}

void progressBarPaladog::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarBack->getWidth(), _progressBarForward->getHeight());
}

void progressBarPaladog::render()
{
	IMAGEMANAGER->render("barBack3", getMemDC(),
		_rcProgress.left + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		0, 0,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	IMAGEMANAGER->render("barForward3", getMemDC(),
		_rcProgress.left + _progressBarForward->getWidth() / 2,
		_y + _progressBarForward->getHeight() / 2,
		0, 0,
		_width, _progressBarForward->getHeight());
}

void progressBarPaladog::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}
