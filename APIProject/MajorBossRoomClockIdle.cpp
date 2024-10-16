#include "pch.h"
#include "MajorBossRoomClockIdle.h"

#include "BitMapManager.h"

void MajorBossRoomClockIdle::Init()
{
	mTransform.SetWorldPosition({ 752, 496 });
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/BG/Chapter04Boss/Spr_Chap4_BossRoom_ClockIdle.bmp", L"MajorBossRoom_ClockIdle");
	AddComponent<SpriteRenderer>(3);
	AddComponent<Animator>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	GetComponent<Animator>()->Loop(true);
	GetComponent<Animator>()->MotionChange(BitMapManager::GetInstance().FindImage(L"MajorBossRoom_ClockIdle"), 0, 18, 701, 799, 0.2f);
}
