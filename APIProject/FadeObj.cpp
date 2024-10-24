#include "pch.h"
#include "FadeObj.h"

#include "Fade.h"
#include "ImageManager.h"

void FadeObj::Init()
{
	mTransform.SetWorldPosition({ 960.f, 540.f });
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/Fade.png", L"Fade");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"Fade"), 3840.f, 2160.f, 50)->SetFrame(0);
	AddComponent<Fade>();
}
