#include "pch.h"
#include "BlackBGObj.h"

#include "ImageManager.h"

void BlackBGObj::Init()
{
	mTransform.SetWorldPosition({ WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f });
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/Fade.png", L"Fade");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"Fade"), 3840.f, 2160.f, 0)->SetFrame(0);
	AddComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
}
