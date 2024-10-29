#include "pch.h"
#include "PrologueScene.h"

#include "GameObjectManager.h"
#include "GrabObject.h"
#include "PlayerObject.h"
#include "PrologueMapObj.h"
#include "PrologueSkyObj.h"

void PrologueScene::Init()
{
	GameObjectManager::GetInstance().AddGameObject<PrologueMapObj>();
	GameObjectManager::GetInstance().AddGameObject<PlayerObject>();
	GameObjectManager::GetInstance().AddGameObject<GrabObject>();
	Camera::GetInstance().SetBoundary(0, 0, 6752.f, 3696.f);
	GameObjectManager::GetInstance().AddGameObject<PrologueSkyObj>();
}
