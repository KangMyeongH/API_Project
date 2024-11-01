#include "pch.h"
#include "BubbleLeft.h"

#include "ImageManager.h"

void BubbleLeft::Init()
{
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Bubble_Left.png", L"Bubble_Left");
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"Bubble_Left"), 4.f, 22.f, 7);
}
