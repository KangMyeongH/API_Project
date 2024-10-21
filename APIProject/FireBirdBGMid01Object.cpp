#include "pch.h"
#include "FireBirdBGMid01Object.h"

#include "ImageManager.h"

void FireBirdBGMid01Object::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/FireBird_BG_Mid01.png", L"BG_Mid01");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"BG_Mid01"), 4150.f, 784.f, 3);
	GetComponent<SpriteRenderer>()->SetFrame(0);
}