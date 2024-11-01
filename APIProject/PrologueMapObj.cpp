#include "pch.h"
#include "PrologueMapObj.h"

#include "EdgeCollider.h"
#include "ImageManager.h"

void PrologueMapObj::Init()
{
	mTransform.SetWorldPosition({ 3376.f,1848.f });
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Prologue.png", L"Prologue");
	AddComponent<SpriteRenderer>(
	ImageManager::GetInstance().FindImage(L"Prologue"),
		6752.f,
		3696.f,
		3)->SetFrame(0);

}
