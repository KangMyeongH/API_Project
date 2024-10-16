#include "pch.h"
#include "MajorBossRoomBG.h"

#include "BitMapManager.h"
#include "ImageManager.h"

void MajorBossRoomBG::Init()
{
	mTransform.SetWorldPosition({ 752, 496 });
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/Chapter04Boss/Spr_Chap4_BossRoom_BG.png", L"MajorBossRoom_BG");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"MajorBossRoom_BG"), 2590.f, 880.f, 1);
	GetComponent<SpriteRenderer>()->SetFrame(0);
}