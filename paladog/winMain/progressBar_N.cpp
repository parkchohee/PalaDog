#include "stdafx.h"
#include "progressBar_N.h"


progressBar_N::progressBar_N()
{
}


progressBar_N::~progressBar_N()
{
}

HRESULT progressBar_N::init(int x, int y, int width, int height, string fImageName, string sImageName)
{
	_x = x;
	_y = y;
	char str[100];
	fImage = fImageName;
	sImage = sImageName;

	_rcProgress = RectMake(x, y, width, height);
	/*_progressBarForward = IMAGEMANAGER->findImage(fImageName);
	_progressBarBack = IMAGEMANAGER->findImage(sImageName);

	_progressBarForward->setX(x);
	_progressBarForward->setY(y);
	_progressBarForward->setWidth(width);
	_progressBarForward->setHeight(height);

	_progressBarBack->setX(x);
	_progressBarBack->setY(y);
	_progressBarBack->setWidth(width);
	_progressBarBack->setHeight(height);*/

	sprintf_s(str, "image/%s.bmp", fImageName.c_str());
	_progressBarForward = IMAGEMANAGER->addImage(fImageName, str, x, y, width, height, true, RGB(255, 0, 255));
	sprintf_s(str, "image/%s.bmp", sImageName.c_str());
	_progressBarBack = IMAGEMANAGER->addImage(sImageName, str, x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarForward->getWidth();

	return S_OK;
}

void progressBar_N::release()
{
}

void progressBar_N::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarBack->getWidth(), _progressBarForward->getHeight());
}

void progressBar_N::render()
{
	IMAGEMANAGER->render(sImage, getMemDC(),
		_rcProgress.left + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		0, 0,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	IMAGEMANAGER->render(fImage, getMemDC(),
		_rcProgress.left + _progressBarForward->getWidth() / 2,
		_y + _progressBarForward->getHeight() / 2,
		0, 0,
		_width, _progressBarForward->getHeight());
}

void progressBar_N::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}
