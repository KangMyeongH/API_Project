#include "pch.h"
#include "JusinLogoObj.h"

#include "ImageManager.h"
#include "JusinLogo.h"

void JusinLogoObj::Init()
{
	mTransform.SetWorldPosition({ 960.f, 540.f });
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/jusinlogo.png", L"jusinlogo");
	AddComponent<SpriteRenderer>(
		ImageManager::GetInstance().FindImage(L"jusinlogo"),
		343,
		285,
		5)->SetFrame(0);
	AddComponent<JusinLogo>();
}
