#include "pch.h"
#include "FireBirdBGObject.h"

#include "ImageManager.h"

void FireBirdBGObject::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/Spr_Chaper4_BG_Sky.png", L"FireBird_Sky");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"FireBird_Sky"), 1920.f, 711.f, 1);
	//AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"FireBird_Sky"), 4150.f, 784.f, 1);
	GetTransform()->SetWorldPosition({ 960.f,100.5f });
	GetComponent<SpriteRenderer>()->SetFrame(0);
	GetComponent<SpriteRenderer>()->SetScale(10.f);
}
