#include "pch.h"
#include "FireBirdObj.h"

#include "BoxCollider.h"
#include "FireBird.h"
#include "ImageManager.h"

void FireBirdObj::Init()
{
	//ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/body/BOSS_Firebird_Body_Idle.png", L"BOSS_Firebird_Body_Idle");
	//ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/body/BOSS_Firebird_Body_Idle.png", L"BOSS_Firebird_Body_Idle");

	//AddComponent<SpriteRenderer>(5);


	AddComponent<BoxCollider>();
	AddComponent<Rigidbody>(0, false, 1.f, 0, DYNAMIC);
	AddComponent<FireBird>();
	mTag = BOSS;
	mTransform.SetLocalScale({ 300,350 });
}
