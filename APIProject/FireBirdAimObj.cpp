#include "pch.h"
#include "FireBirdAimObj.h"

#include "BoxCollider.h"
#include "FireBirdAim.h"
#include "ImageManager.h"

void FireBirdAimObj::Init()
{
	mTag = BULLET;
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdAim_Incendiary_Appear.png", L"FirebirdAim_Incendiary_Appear");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdAim_Incendiary_Aim.png", L"FirebirdAim_Incendiary_Aim");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdAim_Incendiary_AttackLoop.png", L"FirebirdAim_Incendiary_AttackLoop");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdVFX_ShootExplode.png", L"FirebirdVFX_ShootExplode");


	AddComponent<BoxCollider>();
	AddComponent<Rigidbody>(0, false, 1.f, 0, DYNAMIC);
	AddComponent<FireBirdAim>();
	AddComponent<SpriteRenderer>(11);
	AddComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	mTransform.SetLocalScale({ 50.f,50.f });
}
