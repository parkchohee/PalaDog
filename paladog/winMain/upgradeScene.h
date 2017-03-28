#pragma once
#include "gameNode.h"
#include "progressBar.h"
#define SLOTMAX 9
enum state
{
	LOCK,
	UNSHOW,
	SHOW,
	SHOWCLICK
};

struct tagState
{
	int lev;
	int hp;
	int attack;
	int speed;
	int delay;
	int upgradeAttack;
	int upgradeHp;
	int upgradeGold;
};

struct tagUnitSlot
{
	image* image;
	tagState unitState;
	RECT rc;
	int x, y;
	state state;
	char imageName[32];
};

struct tagShowImage
{
	image* showImage; //클릭시 옆에 나오는 이미지
	image* showImageName;
	RECT rc;
	RECT nameRc;
	char imageName[32];
	int x, y;
};

struct tagUpImage
{
	image* attackUp;
	image* hpUp;
	image* goldUp;
	RECT aRc;
	RECT hRc;
	RECT gRc;
	int aFrameX, hFrameX, gFrameX;
};

struct tagGold
{
	image* image;
	RECT rc;
	int frameX;
	int x, y;
};

struct tagBtnUpgrade
{
	image* image;
	RECT rc;
	int frameX;
	bool isUse;
	bool isClick;
};

struct tagLevImage
{
	image* firstImage;
	image* secondImage;
	RECT rc[2];
	int firstFrame;
	int secondFrameX;
};

class upgradeScene : public gameNode
{
private:
	image* _bgImage;
	tagUnitSlot _unitSlot[SLOTMAX];
	tagShowImage _showImage;
	tagGold _goldImage_w[8]; //하얀색 이미지
	tagUpImage _upImage[10];
	tagBtnUpgrade _btnUpgrade;
	tagLevImage _levImage[4]; //레벨은 20까지오니.
	tagGold _btnNext;
	int _frameX;
	int _count;
	int _gold;
	int _selectSlotNum;

	progressBar* _hpBar;
	progressBar* _attackBar;
	progressBar* _speedBar;
	progressBar* _delayBar;
public:
	upgradeScene();
	~upgradeScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
	void showImage();
	void frameCount();
	void goldImage();
	void goldRender();
	void unitStateInfo();
	void unitUpgeadeInfo();
	void showUpgradeImage(int unitNum);
	void upgradeUse();
	void upgradeClick();
	void unitLevUp();
	void setSlotFrame();
	void levImage();
	void btnNextTouch();
};
