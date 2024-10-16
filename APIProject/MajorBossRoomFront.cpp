#include "pch.h"
#include "MajorBossRoomFront.h"

#include "BitMapManager.h"
#include "EdgeCollider.h"
#include "ImageManager.h"

void MajorBossRoomFront::Init()
{
	mTransform.SetWorldPosition({ 752, 496 });
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/Chapter04Boss/Spr_Chap4_BossRoom_Front.png", L"MajorBossRoom_Front");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"MajorBossRoom_Front"), 1504.f, 992.f, 4);
	AddComponent<EdgeCollider>(POINT({ 0,848 }), POINT({ 1504,848 }));
	GetComponent<SpriteRenderer>()->SetFrame(0);
	
}
