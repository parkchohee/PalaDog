#include "stdafx.h"
#include "gameStudy.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init(true);

	// startScene 이미지
	IMAGEMANAGER->addFrameImage("playBtn", "image/playBtn.bmp", 283, 330, 1, 2, true, RGB(255, 0, 255));	// 시작버튼
	IMAGEMANAGER->addFrameImage("selectSlotCloseBtn", "image/selectSlotCloseBtn.bmp", 162, 81, 2, 1, true, RGB(255, 0, 255));	// 슬롯닫기버튼
	IMAGEMANAGER->addImage("selectSlot", "image/selectSlot.bmp", 678, 540, true, RGB(255, 0, 255));	// 슬롯 창
	IMAGEMANAGER->addImage("selectSlotCloseBtn", "image/selectSlotCloseBtn.bmp", 85, 70, true, RGB(255, 0, 255));	// 슬롯 창 닫기 버튼
	IMAGEMANAGER->addImage("playerList", "image/playerList.bmp", 583, 139, true, RGB(255, 0, 255));	// 슬롯 창 플레이어 리스트
	IMAGEMANAGER->addImage("playerListEmpty", "image/playerListEmpty.bmp", 583, 139, true, RGB(255, 0, 255));	// 슬롯 창 플레이어 리스트 비어있을때
	IMAGEMANAGER->addImage("main_cloud_top", "image/main_cloud_top.bmp", 969, 122, true, RGB(255, 0, 255));	// 구름 위
	IMAGEMANAGER->addImage("main_cloud_bottom", "image/main_cloud_bottom.bmp", 969, 122, true, RGB(255, 0, 255));	// 구름 아래
	IMAGEMANAGER->addImage("main_mountain_big", "image/main_mountain_big.bmp", 854, 450, true, RGB(255, 0, 255));	// 산1
	IMAGEMANAGER->addImage("main_mountain_small", "image/mountain_small.bmp", 289, 218, true, RGB(255, 0, 255));	// 산2
	IMAGEMANAGER->addImage("main_logo", "image/main_logo.bmp", 704, 200, true, RGB(255, 0, 255));	// 로고
	IMAGEMANAGER->addFrameImage("main_vol", "image/main_vol.bmp", 3890, 300, 6, 1, true, RGB(255, 0, 255));	// 화산
	IMAGEMANAGER->addFrameImage("stand_dog", "image/stand_dog.bmp", 750, 300, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("startBtn", "image/startBtn.bmp", 108, 54, true, RGB(255, 0, 255));	// 시작버튼
	IMAGEMANAGER->addImage("deleteBtn", "image/deleteBtn.bmp", 100, 46, true, RGB(255, 0, 255));	// 삭제버튼
	IMAGEMANAGER->addImage("tree", "image/tree.bmp", 960, 374, true, RGB(255, 0, 255));	// 나무

	// newPlayerScene
	IMAGEMANAGER->addImage("newPlayer01", "image/newPlayer01.bmp", 960, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("newPlayer02", "image/newPlayer02.bmp", 960, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("newPlayer03", "image/newPlayer03.bmp", 960, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("newPlayer04", "image/newPlayer04.bmp", 960, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("newPlayer05", "image/newPlayer05.bmp", 960, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("newPlayer06", "image/newPlayer06.bmp", 960, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("newPlayerNextBtn", "image/newPlayerNextBtn.bmp", 180, 70, true, RGB(255, 0, 255));


	// selectScene
	IMAGEMANAGER->addImage("selectStage", "image/stageSelect2.bmp", 960, 540, false, false);
	IMAGEMANAGER->addImage("stage1", "image/stage_1.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage2", "image/stage_2.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage3", "image/stage_3.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage4", "image/stage_4.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage5", "image/stage_5.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage6", "image/stage_6.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage7", "image/stage_7.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage8", "image/stage_8.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage9", "image/stage_9.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage10", "image/stage_10.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage11", "image/stage_11.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage12", "image/stage_12.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stageLock", "image/stage_lock.bmp", 100, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stageStroke", "image/stage_stroke.bmp", 124, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stageStar", "image/stage_star.bmp", 63, 60, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("btnUpgrade", "image/btn_upgrade.bmp", 390, 75, 2, 1, true, RGB(255, 0, 255));

	//upgradeScene 이미지
	IMAGEMANAGER->addImage("upgradeUnit", "image/upgrade_unit.bmp", 960, 540, false, false);
	//slot
	IMAGEMANAGER->addImage("slot_lock", "image/slot_lock.bmp", 100, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slot_1m", "image/slot_1m.bmp", 400, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slot_2m", "image/slot_2m.bmp", 400, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slot_3m", "image/slot_3m.bmp", 400, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slot_4m", "image/slot_4m.bmp", 400, 80, 4, 1, true, RGB(255, 0, 255));
	//unitName
	IMAGEMANAGER->addImage("mName", "image/mouseName.bmp", 282, 81, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rName", "image/rabbitName.bmp", 321, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bName", "image/bearName.bmp", 240, 81, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("kName", "image/kangarooName.bmp", 262, 86, true, RGB(255, 0, 255));
	//gold
	IMAGEMANAGER->addFrameImage("goldNum", "image/gold_num.bmp", 336, 32, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goldNum_w", "image/gold_num_w.bmp", 336, 31, 12, 1, true, RGB(255, 0, 255));
	//upgrade
	//upgrade
	IMAGEMANAGER->addFrameImage("upUnitNum", "image/upgradeUnit_num.bmp", 264, 24, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("btnUnUpgrade", "image/btn_unUpgrade.bmp", 585, 75, 3, 1, true, RGB(255, 0, 255));
	//nextBtn
	IMAGEMANAGER->addFrameImage("btnNext", "image/btn_next.bmp", 402, 81, 2, 1, true, RGB(255, 0, 255));




	//levelUp 이미지
	IMAGEMANAGER->addImage("levUpBG", "image/levelUp_slot.bmp", 960, 540, false, false);
	IMAGEMANAGER->addFrameImage("levUpnum", "image/levUp_num.bmp", 456, 44, 12, 1, true, RGB(255, 0, 255));




	// playScene 이미지
	IMAGEMANAGER->addImage("playSceneSlot", "image/playSceneSlot.bmp", 960, 270, true, RGB(255, 0, 255));	// 슬롯
	IMAGEMANAGER->addImage("playSceneBackground", "image/playSceneBackground.bmp", 1639, 370, true, RGB(255, 0, 255));	// 배경
	IMAGEMANAGER->addFrameImage("run_dog", "image/run_dog.bmp", 1870, 300, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("die_dog", "image/dog_die_edit.bmp", 8140, 254, 37, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DieScene", "image/DieScene.bmp", 20160, 540, 21, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Next", "image/Next.bmp", 404, 96, 2, 1, true, RGB(255, 0, 255)); //다이씬 버튼

	// 마법
	IMAGEMANAGER->addFrameImage("MeteoSkill", "image/MeteoSkill.bmp", 7050, 190, 47, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("FireSkill", "image/FireSkill.bmp", 2080, 100, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PunchSkill", "image/PunchSkill.bmp", 350, 60, 5, 1, true, RGB(255, 0, 255));
	//slot
	IMAGEMANAGER->addFrameImage("slot_1", "image/slot_1.bmp", 400, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slot_2", "image/slot_2.bmp", 400, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slot_3", "image/slot_3.bmp", 400, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slot_4", "image/slot_4.bmp", 400, 100, 4, 1, true, RGB(255, 0, 255));
	// 아군
	IMAGEMANAGER->addFrameImage("MouseMove", "image/MouseMove.bmp", 425, 80, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MouseAttack", "image/MouseAttack.bmp", 340, 82, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MouseDie", "image/MouseDie.bmp", 510, 82, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RabbitMove", "image/RabbitMove.bmp", 475, 105, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RabbitAttack", "image/RabbitAttack.bmp", 950, 105, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RabbitDie", "image/RabbitDie.bmp", 760, 105, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrow", "image/frameArrow.bmp", 750, 30, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BearMove", "image/BearMove.bmp", 600, 120, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BearAttack", "image/BearAttack.bmp", 360, 120, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BearDie", "image/BearDie.bmp", 840, 120, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("KangarooMove", "image/KangarooMove.bmp", 1200, 120, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("KangarooAttack", "image/KangarooAttack.bmp", 960, 120, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("KangarooDie", "image/KangarooDie.bmp", 1080, 120, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DethGhost", "image/DethGhost.bmp", 1105, 50, 13, 1, true, RGB(255, 0, 255));
	// 적
	IMAGEMANAGER->addFrameImage("DevilMove", "image/DevilMove.bmp", 380, 95, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DevilAttack", "image/DevilAttack.bmp", 380, 95, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DevilDie", "image/DevilDie.bmp", 570, 95, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossHome", "image/bossHome.bmp", 300, 364, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossHomeUp", "image/bossHomeUp.bmp", 300, 364, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossHomeWeak", "image/bossHomeWeak.bmp", 300, 364, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossHomeWeakUp", "image/bossHomeWeakUp.bmp", 300, 364, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossHomeBroken", "image/bossHomeBroken.bmp", 300, 364, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossHomeBrokenUp", "image/bossHomeBrokenUp.bmp", 300, 364, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("KzombieAttack", "image/KzombieAttack.bmp", 6000, 340, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("KzombieDie", "image/KzombieDie.bmp", 3920, 340, 14, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("KzombieMove", "image/KzombieMove.bmp", 1440, 340, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GhostAttack", "image/monster/GhostAttack.bmp", 950, 95, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GhostDie", "image/monster/GhostDie.bmp", 665, 95, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GhostMove", "image/monster/GhostMove.bmp", 380, 95, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WitchAttack", "image/monster/WitchAttack.bmp", 805, 115, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WitchDie", "image/monster/WitchDie.bmp", 1495, 115, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WitchMove", "image/monster/WitchMove.bmp", 805, 115, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ZombieAttack", "image/monster/ZombieAttack.bmp", 520, 115, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ZombieDie", "image/monster/ZombieDie.bmp", 585, 115, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ZombieMove", "image/monster/ZombieMove.bmp", 325, 115, 5, 1, true, RGB(255, 0, 255));

	// playScene 데코
	IMAGEMANAGER->addImage("psUiTop", "image/psUiTop.bmp", 239, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("psLevel", "image/psLevel.bmp", 55, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("psPause", "image/psPause.bmp", 62, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("psFood", "image/psFood.bmp", 10, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("psMp", "image/psMp.bmp", 10, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("psSlash", "image/psSlash.bmp", 20, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("psMoney", "image/psMoney.bmp", 31, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("psEmpty", "image/psEmpty.bmp", 10, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("psLeft", "image/psLeft.bmp", 216, 66, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("psRight", "image/psRight.bmp", 216, 66, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("psNum", "image/psNum.bmp", 209, 20, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("psNumLevel", "image/psNumLevel.bmp", 110, 11, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("psNumGold", "image/psNumGold.bmp", 209, 20, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("psPunch", "image/psPunch.bmp", 204, 102, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("psMeteo", "image/psMeteo.bmp", 204, 102, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("psFire", "image/psFire.bmp", 204, 102, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aurora", "image/aurora.bmp", 1620, 74, 6, 1, true, RGB(255, 0, 255));

	// ThreeStageScene
	IMAGEMANAGER->addImage("ThreeStageScene", "image/ThreeStageScene.bmp", 960, 540, true, RGB(255, 0, 255));	// 배경
	IMAGEMANAGER->addImage("psUiTop3", "image/psUiTop3.bmp", 250, 35, true, RGB(255, 0, 255));//해골게이지
	IMAGEMANAGER->addImage("MouseWeapon", "image/MouseWeapon.bmp", 100, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RabbitWeapon", "image/RabbitWeapon.bmp", 100, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BearWeapon", "image/BearWeapon.bmp", 100, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("KangarooWeapon", "image/KangarooWeapon.bmp", 100, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3StageFire", "image/3StageFire.bmp", 100, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3StageMeteo", "image/3StageMeteo.bmp", 100, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3StagePunch", "image/3StagePunch.bmp", 100, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("clearWindow", "image/clearWindow.bmp", 500, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("star", "image/star.bmp", 80, 69, false, false);

	//Pause
	IMAGEMANAGER->addImage("pause", "image/Pause.bmp", 500, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("resume", "image/Resume.bmp", 400, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("giveUp", "image/GiveUp.bmp", 400, 100, 2, 1, true, RGB(255, 0, 255));


	// Scene 추가
	SCENEMANAGER->addScene("startScene", new startScene);
	SCENEMANAGER->addScene("stageSelectScene", new stageSelectScene);
	SCENEMANAGER->addScene("playScene", new playScene);
	SCENEMANAGER->addScene("newPlayerScene", new newPlayerScene);
	SCENEMANAGER->addScene("upgradeScene", new upgradeScene);
	SCENEMANAGER->addScene("levelUpScene", new levelUpScene);
	SCENEMANAGER->addScene("threeStageScene", new threeStageScene);
	SCENEMANAGER->addScene("DieScene", new DieScene);

	SCENEMANAGER->changeScene("startScene");

	return S_OK;
}

void gameStudy::release()
{

	gameNode::release();
}

void gameStudy::update()
{
	SCENEMANAGER->update();

	gameNode::update();
}

void gameStudy::render()
{
	//백버퍼에서 뿌려줌
	/*HDC backDC = this->getBackBuffer()->getMemDC();*/
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============================================================

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//============================================================
	//백버퍼에 있는 그림을 HDC에 그리자
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

