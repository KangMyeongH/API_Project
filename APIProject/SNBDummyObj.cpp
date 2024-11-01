#include "pch.h"
#include "SNBDummyObj.h"

#include "ImageManager.h"

void SNBDummyObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"./Sprite/SNB_Sleep.png", L"SNB_Sleep");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/SNB_Awake1.png", L"SNB_Awake1");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/SNB_Awake2.png", L"SNB_Awake2");



	AddComponent<SpriteRenderer>(8);
	AddComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
}
