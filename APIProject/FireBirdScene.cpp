#include "pch.h"
#include "FireBirdScene.h"

#include "FireBirdBGMid01Object.h"
#include "FireBirdBGMid02Object.h"
#include "FireBirdBGObject.h"
#include "GameObjectManager.h"
#include "GrabObject.h"
#include "PlayerObject.h"
#include "ScrollBG.h"
#include "ScrollBGObject.h"

void FireBirdScene::Init()
{
	GameObjectManager::GetInstance().AddGameObject<FireBirdBGObject>();

	GameObject* obj1 = GameObjectManager::GetInstance().AddGameObject<FireBirdBGMid01Object>();
	obj1->GetTransform()->SetWorldPosition({0.f, 690.f});
	GameObject* obj2 = GameObjectManager::GetInstance().AddGameObject<FireBirdBGMid01Object>();
	GameObject* bgScroll1 = GameObjectManager::GetInstance().AddGameObject<ScrollBGObject>();
	bgScroll1->GetComponent<ScrollBG>()->Init(obj1->GetTransform(), obj2->GetTransform(), -1.1f);

	GameObject* obj3 = GameObjectManager::GetInstance().AddGameObject<FireBirdBGMid02Object>();
	obj3->GetTransform()->SetWorldPosition({ 0.f, 640.f });
	GameObject* obj4 = GameObjectManager::GetInstance().AddGameObject<FireBirdBGMid02Object>();
	GameObject* bgScroll2 = GameObjectManager::GetInstance().AddGameObject<ScrollBGObject>();
	bgScroll2->GetComponent<ScrollBG>()->Init(obj3->GetTransform(), obj4->GetTransform(), -0.75f);

	Camera::GetInstance().SetZoom(1.4f);
	GameObjectManager::GetInstance().AddGameObject<PlayerObject>();
	GameObjectManager::GetInstance().AddGameObject<GrabObject>();

}
