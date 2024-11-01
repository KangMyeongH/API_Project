#include "pch.h"
#include "MouseObj.h"

#include "BoxCollider.h"
#include "ImageManager.h"
#include "Mouse.h"

void MouseObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"./Sprite/mouse cursor2.png", L"Cursor");
	AddComponent<BoxCollider>();
	AddComponent<Mouse>();
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"Cursor"), 128.f, 128.f, 20)->SetFrame(0);
	GetComponent<SpriteRenderer>()->SetScale(0.75f);
}
