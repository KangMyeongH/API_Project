#include "pch.h"
#include "MainSceneBGObj.h"

#include "ImageManager.h"
#include "MainSceneBG.h"

void MainSceneBGObj::Init()
{
	mTransform.SetWorldPosition({ 960.f,540.f });
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/UI_MainScene_BG.png", L"UI_MainScene_BG");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"UI_MainScene_BG"), 1920.f, 1080.f, 7)->SetFrame(0);
	AddComponent<MainSceneBG>();
}
