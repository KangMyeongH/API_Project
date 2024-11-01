#include "pch.h"
#include "PrologueCloudObj.h"

#include "ImageManager.h"
#include "PrologueCloud.h"

void PrologueCloudObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/Spr_PRLG_Forest_BG_Mountain.png", L"PRLG_Mountain");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"PRLG_Mountain"), 1426.f, 582.f, 0)->SetFrame(1);
	AddComponent<PrologueCloud>();
}
