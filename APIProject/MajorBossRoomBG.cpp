#include "pch.h"
#include "MajorBossRoomBG.h"

#include "BitMapManager.h"
#include "ImageManager.h"

void MajorBossRoomBG::Init()
{
	mTransform.SetWorldPosition({ 752, 496 });
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/BG/Chapter04Boss/Spr_Chap4_BossRoom_BG.bmp", L"MajorBossRoom_BG");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"MajorBossRoom_BG"), 2590.f, 880.f, 1);
}
// 이미지만 불렀는데 34프레임