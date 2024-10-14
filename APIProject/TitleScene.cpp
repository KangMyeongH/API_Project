#include "pch.h"
#include "TitleScene.h"

#include "GameObjectManager.h"
#include "PlayerObject.h"

void TitleScene::Init()
{
	GameObjectManager::GetInstance().AddGameObject<PlayerObject>();
}
