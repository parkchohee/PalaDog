#pragma once
#include "gameNode.h"

#define MAXPLAYER 3

struct playerInfo
{
	RECT rc;
	int x, y;

	bool isEmpty;
	bool isSelect;

	RECT selectRc;
	RECT deleteRc;

	char fileName[16];

	int lev;
	int star;
	int gold;
	int time;
};

struct tagInfo
{
	image* lvImage[2];
	image* stImage[2];
	image* goldImage[8];
	image* timeIamge[6];

	int levFrameX[2];
	int stFrameX[2];
	int goldFrameX[8];
	int timeFrameX[6];

	RECT lvRc[2];
	RECT stRc[2];
	RECT goldRc[8];
	RECT timeRc[6];
};

class startScene : public gameNode
{
	RECT _startBtn;

	RECT _selectSlot;
	RECT _selectSlotCloseBtn;

	playerInfo _playerList[MAXPLAYER];
	tagInfo _infoList[MAXPLAYER];

	int _selectPlayerNum;
	bool _isStart;

	// loop, frame 돌리기
	int _offsetX, _offsetY;
	int _count;
	int _currentFrameX;

	// start버튼 프레임
	int _startBtnFrameY;
	int _closeBtnFrameX;




public:
	startScene();
	~startScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
	void frameCount();

	void playerDataInit();
	void loadPlayerData(const char* fileName, int i);
	void createPlayerData(const char* fileName);
	void deletePlayerData(const char* fileName);
	void setInfo();
	void showImageInfo();
};

