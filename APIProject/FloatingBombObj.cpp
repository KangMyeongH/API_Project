#include "pch.h"
#include "FloatingBombObj.h"

#include "BoxCollider.h"
#include "Enemy.h"
#include "FloatingBomb.h"
#include "ImageManager.h"

void FloatingBombObj::Init()
{
	mTag = ENEMY;
	ImageManager::GetInstance().InsertBmp(L"./Sprite/04. Boss/00. FireBird/bomb/FloatingBomb_Excholded_Back_lp.png", L"FloatingBomb_Excholded_Back_lp");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/04. Boss/00. FireBird/bomb/FloatingBomb_Excholded_Front_lp.png", L"FloatingBomb_Excholded_Front_lp");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/04. Boss/00. FireBird/bomb/FloatingBomb_Excholded_Neu_lp.png", L"FloatingBomb_Excholded_Neu_lp");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/04. Boss/00. FireBird/bomb/FloatingBomb_ExcholdedStart.png", L"FloatingBomb_ExcholdedStart");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/04. Boss/00. FireBird/bomb/FloatingBomb_ExplodeHuge.png", L"FloatingBomb_ExplodeHuge");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/04. Boss/00. FireBird/bomb/FloatingBomb_Idle_lp.png", L"FloatingBomb_Idle_lp");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/04. Boss/00. FireBird/bomb/FloatingBomb_Knockback.png", L"FloatingBomb_Knockback");

	mTransform.SetLocalScale({ 44.f,36.f });
	AddComponent<BoxCollider>();
	AddComponent<SpriteRenderer>(6);
	AddComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	AddComponent<FloatingBomb>();
	AddComponent<Enemy>(EXC_FLY);
}
