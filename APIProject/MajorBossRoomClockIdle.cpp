#include "pch.h"
#include "MajorBossRoomClockIdle.h"

#include "BitMapManager.h"
#include "ImageManager.h"

void MajorBossRoomClockIdle::Init()
{
	mTransform.SetWorldPosition({ 752, 496 });
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/MajorBossBG/Chap4_BossRoom_ClockworkIdle.png", L"MajorBossRoom_ClockIdle");
	AddComponent<SpriteRenderer>(3);
	AddComponent<Animator>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	GetComponent<Animator>()->Loop(true);
	GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"MajorBossRoom_ClockIdle"), 0, 18, 700, 800, 0.2f);
}
