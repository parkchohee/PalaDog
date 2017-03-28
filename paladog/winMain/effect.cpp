#include "stdafx.h"
#include "effect.h"
#include "animation.h"

effect::effect() : _effectImage(NULL), _effectAnimation(NULL),
_isRunning(FALSE), _elapsedTime(0), _x(0), _y(0)
{
}


effect::~effect()
{
}

HRESULT effect::init( image * effectImage, int frameW, int frameH, int fps, float elapsedTime )
{
	//���࿡ �̹����� ������ ��������
	if ( !effectImage ) return E_FAIL;

	//.Ȱ��ȭ ���� �ʱ�ȭ 
	_isRunning = false;

	//����Ʈ �̹��� ���� ����
	_effectImage = effectImage;

	//����Ʈ ��� �ð�
	_elapsedTime = elapsedTime;

	//�̹��� �ִϸ��̼� ��ü�� ������ ����������
	if ( !_effectAnimation ) _effectAnimation = new animation;

	//�ִϸ��̼� ���� ����
	_effectAnimation->init( _effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH );
	_effectAnimation->setDefPlayFrame();
	_effectAnimation->setFPS( fps );
	_effectAnimation->stop();

	return S_OK;
}

void effect::release()
{
	_effectImage = NULL;

	if ( _effectAnimation )
	{
		SAFE_DELETE( _effectAnimation );
	}
}


void effect::update()
{
	//Ȱ��ȭ ���� �ʾ����� ��������ָ� �ȵȴ�.
	if ( !_isRunning ) return;

	_effectAnimation->frameUpdate( _elapsedTime );

	//����Ʈ �ִϸ��̼��� ���� �Ǹ� kill���ش�
	if ( !_effectAnimation->isPlay() ) killEffect();
}

void effect::render()
{
	//������� �ʾ����� �׷������� ���ƶ�
	if ( !_isRunning ) return;

	//Effect �ִϸ��̼� �׷���
	_effectImage->aniRender( getMemDC(), _x, _y, _effectAnimation );
}

void effect::startEffect( int x, int y )
{
	//����Ʈ ������ �ʱ�ȭ �Ǿ����� �ʴٸ� ������� ����.
	if ( !_effectImage || !_effectAnimation ) return;

	//x, y ��ǥ�� ����Ʈ ž�̹Ƿ� �߾���ǥ�� �ٲ�����
	_x = x - ( _effectAnimation->getFrameWidth() / 2 );
	_y = y - ( _effectAnimation->getFrameHeight() / 2 );

	_isRunning = TRUE;
	_effectAnimation->start();
}

void effect::killEffect()
{
	_isRunning = FALSE;
}
