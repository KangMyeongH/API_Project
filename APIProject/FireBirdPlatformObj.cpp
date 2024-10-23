#include "pch.h"
#include "FireBirdPlatformObj.h"

#include "BoxCollider.h"
#include "FireBirdPlatform.h"
#include "ImageManager.h"
#include "Platform.h"


void FireBirdPlatformObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/00. Platform/FireBird_PlatformA_Idle.png", L"FireBird_PlatformA_Idle");
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/00. Platform/FireBird_PlatformA_IdleWarning.png", L"FireBird_PlatformA_IdleWarning");
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/00. Platform/FireBird_PlatformA_IdleDoubleWarning.png", L"FireBird_PlatformA_IdleDoubleWarning");
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/00. Platform/FireBird_PlatformA_Damaged.png", L"FireBird_PlatformA_Damaged");
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/00. Platform/FireBird_PlatformA_DamagedWarning.png", L"FireBird_PlatformA_DamagedWarning");
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/00. Platform/FireBird_PlatformA_Destroy.png", L"FireBird_PlatformA_Destroy");
	ImageManager::GetInstance().InsertBmp(L"Sprite/BG/FireBird/00. Platform/FireBird_PlatformA_Dead.png", L"FireBird_PlatformA_Dead");



	mTag = PLATFORM;
	mTransform.SetLocalScale({ 250.f, 100.f });
	AddComponent<Rigidbody>(0, false, 10.f, 0, DYNAMIC);
	AddComponent<BoxCollider>()->SetOffset({ 0, -20 });
	AddComponent<SpriteRenderer>(6);
	AddComponent<Animator>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	GetComponent<Animator>()->Loop(true);
	GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"FireBird_PlatformA_Idle"), 0, 4, 304, 192, 0.05f);
	AddComponent<Platform>();
	GetComponent<Platform>()->SetGrab(true);
	GetComponent<Platform>()->SetHit(true);
	AddComponent<FireBirdPlatform>();
}
