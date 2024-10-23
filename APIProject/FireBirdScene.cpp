#include "pch.h"
#include "FireBirdScene.h"

#include "FireBirdBGMid01Object.h"
#include "FireBirdBGMid02Object.h"
#include "FireBirdBGObject.h"
#include "FireBirdObj.h"
#include "FireBirdPlatformObj.h"
#include "GameObjectManager.h"
#include "GrabObject.h"
#include "PlayerObject.h"
#include "ScrollBG.h"
#include "ScrollBGObject.h"

void FireBirdScene::Init()
{
	// ���� ���� ũ��
	Camera::GetInstance().SetBoundary(0, 0, 2800.f, 1600.f);
	GameObjectManager::GetInstance().AddGameObject<FireBirdBGObject>();

	GameObject* obj1 = GameObjectManager::GetInstance().AddGameObject<FireBirdBGMid01Object>();
	obj1->GetTransform()->SetWorldPosition({ 0.f, 690.f });
	GameObject* obj2 = GameObjectManager::GetInstance().AddGameObject<FireBirdBGMid01Object>();
	GameObject* bgScroll1 = GameObjectManager::GetInstance().AddGameObject<ScrollBGObject>();
	bgScroll1->GetComponent<ScrollBG>()->Init(obj1->GetTransform(), obj2->GetTransform(), -1.1f);

	GameObject* obj3 = GameObjectManager::GetInstance().AddGameObject<FireBirdBGMid02Object>();
	obj3->GetTransform()->SetWorldPosition({ 0.f, 640.f });
	GameObject* obj4 = GameObjectManager::GetInstance().AddGameObject<FireBirdBGMid02Object>();
	GameObject* bgScroll2 = GameObjectManager::GetInstance().AddGameObject<ScrollBGObject>();
	bgScroll2->GetComponent<ScrollBG>()->Init(obj3->GetTransform(), obj4->GetTransform(), -0.75f);

	GameObjectManager::GetInstance().AddGameObject<FireBirdObj>()->GetTransform()->SetWorldPosition({ 1400.f,1800.f });

	// �һ� �������� �÷������� ������ x = 1000, y = 350 �̴�.
	// ������ ��� �ΰ��� ��ġ
	// ���� ������ x = 400 �� ��ġ
	// �� �� �÷����� y = 525

	// ������ ��ġ��
	GameObjectManager::GetInstance().AddGameObject<FireBirdPlatformObj>()->GetTransform()->SetWorldPosition({ 400.f, 875.f });
	GameObjectManager::GetInstance().AddGameObject<FireBirdPlatformObj>()->GetTransform()->SetWorldPosition({ 1400.f, 875.f });
	GameObjectManager::GetInstance().AddGameObject<FireBirdPlatformObj>()->GetTransform()->SetWorldPosition({ 2400.f, 875.f });

	GameObjectManager::GetInstance().AddGameObject<FireBirdPlatformObj>()->GetTransform()->SetWorldPosition({ 900.f, 525.f });
	GameObjectManager::GetInstance().AddGameObject<FireBirdPlatformObj>()->GetTransform()->SetWorldPosition({ 1900.f, 525.f });

	GameObjectManager::GetInstance().AddGameObject<FireBirdPlatformObj>()->GetTransform()->SetWorldPosition({ 900.f, 1225.f });
	GameObjectManager::GetInstance().AddGameObject<FireBirdPlatformObj>()->GetTransform()->SetWorldPosition({ 1900.f,1225.f });

	Camera::GetInstance().SetZoom(1.4f);
	GameObjectManager::GetInstance().AddGameObject<PlayerObject>()->GetTransform()->SetWorldPosition({ 1400.f,830.f });
	GameObjectManager::GetInstance().AddGameObject<GrabObject>();


}
