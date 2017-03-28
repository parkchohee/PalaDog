#pragma once

#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;							//����Ʈ ��ǥ ��ġX
	int _y;							//����Ʈ �·� ��ġY

	image* _effectImage;			//����Ʈ �̹���
	animation* _effectAnimation;	//����Ʈ �ִϸ��̼�
	BOOL _isRunning;				//����Ʈ Ȱ��ȭ ����
	float _elapsedTime;				//����Ʈ ��� �ð�

public:
	effect();
	~effect();
	
	HRESULT init( image *effectImage, int frameW, int frameH, int fps, float elapsedTime );
	void update();
	void release();
	void render();

	void startEffect( int x, int y );
	void killEffect();

	BOOL getIsRunning() { return _isRunning; }
};

