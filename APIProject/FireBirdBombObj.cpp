#include "pch.h"
#include "FireBirdBombObj.h"

#include "BoxCollider.h"
#include "FireBirdBomb.h"
#include "ImageManager.h"

void FireBirdBombObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FireBirdVFX_Bomb_Appear.png", L"FireBirdVFX_Bomb_Appear");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FireBirdVFX_Bomb_Explode.png", L"FireBirdVFX_Bomb_Explode");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdVFX_Bomb_Falling.png", L"FirebirdVFX_Bomb_Falling");

	// 16 35
	AddComponent<BoxCollider>();
	AddComponent<Rigidbody>(0, false, 0, 0, DYNAMIC);
	AddComponent<SpriteRenderer>(7);
	AddComponent<Animator>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	AddComponent<FireBirdBomb>();
	mTag = BULLET;
	mTransform.SetLocalScale({ 16,35 });
}
