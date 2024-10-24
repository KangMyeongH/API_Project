#include "pch.h"
#include "SNBLogoObj.h"

#include "ImageManager.h"
#include "SNBLogo.h"


void SNBLogoObj::Init()
{
	mTransform.SetWorldPosition({ 1354.f, 245.f});
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/Spr_Logo.png", L"Spr_Logo");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"Spr_Logo"), 930.f, 369.f, 7)->SetFrame(0);
	AddComponent<SNBLogo>();
}
