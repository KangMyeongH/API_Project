#include "pch.h"
#include "FireBirdObj.h"

#include "BoxCollider.h"
#include "FireBird.h"
#include "ImageManager.h"

void FireBirdObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/body/BOSS_Firebird_Body_Idle.png", L"BOSS_Firebird_Body_Idle");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/body/BOSS_FirebirdBroken_Body_Idle.png", L"BOSS_FirebirdBroken_Body_Idle");

	//ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/gun/BOSS_Firebird_Gun_Appear.png", L"BOSS_Firebird_Gun_Appear");
	//ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/gun/BOSS_Firebird_Gun_ShootEnd.png", L"BOSS_Firebird_Gun_ShootEnd");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/gun/BOSS_Firebird_Gun_ShootLoop.png", L"BOSS_Firebird_Gun_ShootLoop");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/gun/BOSS_Firebird_Gun_ShootReadyLoop.png", L"BOSS_Firebird_Gun_ShootReadyLoop");

	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_DownLoop01.png", L"BOSS_Firebird_Wing_DownLoop01");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_DownLoop02.png", L"BOSS_Firebird_Wing_DownLoop02");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_DownLoop03.png", L"BOSS_Firebird_Wing_DownLoop03");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_DownLoop04.png", L"BOSS_Firebird_Wing_DownLoop04");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_NeuLoop.png", L"BOSS_Firebird_Wing_NeuLoop");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_UpLoop01.png", L"BOSS_Firebird_Wing_UpLoop01");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_UpLoop02.png", L"BOSS_Firebird_Wing_UpLoop02");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_UpLoop03.png", L"BOSS_Firebird_Wing_UpLoop03");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_Firebird_Wing_UpLoop04.png", L"BOSS_Firebird_Wing_UpLoop04");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_DownLoop01.png", L"BOSS_FirebirdBroken_Wing_DownLoop01");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_DownLoop02.png", L"BOSS_FirebirdBroken_Wing_DownLoop02");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_DownLoop03.png", L"BOSS_FirebirdBroken_Wing_DownLoop03");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_DownLoop04.png", L"BOSS_FirebirdBroken_Wing_DownLoop04");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_NeuLoop.png", L"BOSS_FirebirdBroken_Wing_NeuLoop");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_UpLoop01.png", L"BOSS_FirebirdBroken_Wing_UpLoop01");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_UpLoop02.png", L"BOSS_FirebirdBroken_Wing_UpLoop02");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_UpLoop03.png", L"BOSS_FirebirdBroken_Wing_UpLoop03");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/wing/BOSS_FirebirdBroken_Wing_UpLoop04.png", L"BOSS_FirebirdBroken_Wing_UpLoop04");


	AddComponent<SpriteRenderer>(5);
	AddComponent<Animator>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());

	AddComponent<BoxCollider>();
	AddComponent<Rigidbody>(0, false, 1.f, 0, DYNAMIC);
	AddComponent<FireBird>();
	mTag = BOSS;
	mTransform.SetLocalScale({ 300,350 });
}
