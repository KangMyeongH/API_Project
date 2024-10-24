#include "pch.h"
#include "TitleScene.h"

#include "BlackBGObj.h"
#include "GameObjectManager.h"
#include "JusinLogoObj.h"
#include "MainTitleBGObj.h"
#include "MouseObj.h"

void TitleScene::Init()
{
	GameObjectManager::GetInstance().AddGameObject<MouseObj>();
	GameObjectManager::GetInstance().AddGameObject<BlackBGObj>();
	GameObjectManager::GetInstance().AddGameObject<JusinLogoObj>();
	GameObjectManager::GetInstance().AddGameObject<MainTitleBGObj>();
}
