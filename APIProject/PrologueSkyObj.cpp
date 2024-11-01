#include "pch.h"
#include "PrologueSkyObj.h"

#include "EdgeCollider.h"
#include "ImageManager.h"
#include "PrologueSky.h"

void PrologueSkyObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/Spr_PRLG_Forest_BG_Sky.png", L"PRLG_Sky");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"PRLG_Sky"), 800.f, 400.f, 0)->SetFrame(0);
	GetComponent<SpriteRenderer>()->SetScale(3.f);
	AddComponent<PrologueSky>();
}
