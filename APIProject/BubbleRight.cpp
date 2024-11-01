#include "pch.h"
#include "BubbleRight.h"

#include "ImageManager.h"

void BubbleRight::Init()
{
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Bubble_Right.png", L"Bubble_Right");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"Bubble_Right"), 4.f, 22.f, 7);
}
