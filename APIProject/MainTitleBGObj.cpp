#include "pch.h"
#include "MainTitleBGObj.h"

#include "ImageManager.h"
#include "MainTitleBG.h"

void MainTitleBGObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/Spr_MainTitle_BlueLED.png", L"Spr_MainTitle_BlueLED");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/Spr_MainTitle_LightOn.png", L"Spr_MainTitle_LightOn");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/Spr_MainTitle_LightOff.png", L"Spr_MainTitle_LightOff");


	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"Spr_MainTitle_BlueLED"), 1920.f, 1080.f, 1);
	AddComponent<MainTitleBG>();
}
