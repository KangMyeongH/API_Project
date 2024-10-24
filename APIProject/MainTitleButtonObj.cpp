#include "pch.h"
#include "MainTitleButtonObj.h"

#include "BoxCollider.h"
#include "ImageManager.h"
#include "MainTitleButton.h"

void MainTitleButtonObj::Init()
{
	// 358.f, 61.f
	// 179
	mTransform.SetWorldPosition({ 1705.f,664.f });
	mTransform.SetLocalScale({ 358.f,61.f });
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/UI_MainScene_SelectBox_Selected.png", L"SelectBox_Selected");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/BG/UI_MainScene_SelectBox.png", L"SelectBox");

	AddComponent<BoxCollider>();
	AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"SelectBox"), 358.f, 61.f, 8)->SetFrame(0);
	AddComponent<MainTitleButton>();
}
