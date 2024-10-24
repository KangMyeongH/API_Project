#include "pch.h"
#include "FireBirdClusterAimObj.h"

#include "BoxCollider.h"
#include "FireBirdClusterAim.h"
#include "ImageManager.h"

void FireBirdClusterAimObj::Init()
{
	mTag = BULLET;
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdAim_Cluster_Aim.png", L"FirebirdAim_Cluster_Aim");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdAim_Cluster_Shoot.png", L"FirebirdAim_Cluster_Shoot");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdVFX_ClusterBomb_Appear.png", L"FirebirdVFX_ClusterBomb_Appear");
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FirebirdVFX_ClusterBomb_Explode.png", L"FirebirdVFX_ClusterBomb_Explode");


	AddComponent<BoxCollider>();
	AddComponent<Rigidbody>(0, false, 1.f, 0, DYNAMIC);
	AddComponent<FireBirdClusterAim>();
	AddComponent<SpriteRenderer>(11);
	AddComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	mTransform.SetLocalScale({ 50.f,50.f });
}
