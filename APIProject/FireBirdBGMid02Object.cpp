#include "pch.h"
#include "FireBirdBGMid02Object.h"

#include "ImageManager.h"

void FireBirdBGMid02Object::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/FireBird_BG_Mid02.png", L"BG_Mid02");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"BG_Mid02"), 3320.f, 784.f, 2);
	GetComponent<SpriteRenderer>()->SetFrame(0);
}
