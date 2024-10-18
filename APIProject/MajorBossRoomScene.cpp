#include "pch.h"
#include "MajorBossRoomScene.h"

#include "EnemyObject.h"
#include "GameObjectManager.h"
#include "GrabObject.h"
#include "MajorBossRoomBG.h"
#include "MajorBossRoomClockIdle.h"
#include "MajorBossRoomFront.h"
#include "PlayerObject.h"

void MajorBossRoomScene::Init()
{
	GameObjectManager::GetInstance().AddGameObject<MajorBossRoomBG>();
	//GameObjectManager::GetInstance().AddGameObject<MajorBossRoomClockIdle>();
	GameObjectManager::GetInstance().AddGameObject<MajorBossRoomFront>();
	GameObjectManager::GetInstance().AddGameObject<PlayerObject>();
	GameObjectManager::GetInstance().AddGameObject<EnemyObject>();
	GameObjectManager::GetInstance().AddGameObject<GrabObject>();
}
