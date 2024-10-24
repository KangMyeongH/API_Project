#include "pch.h"
#include "FireBirdClusterAim.h"

#include "BoxCollider.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "Transform.h"

class Rigidbody;

void FireBirdClusterAim::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}

void FireBirdClusterAim::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();
	GetTransform()->SetWorldPosition(mPlayer->GetTransform()->GetWorldPosition());

	mAnimationMap.insert({ L"FirebirdAim_Cluster_Aim",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdAim_Cluster_Aim"), 0, 24, 256, 256, 0.2f, false) });
	mAnimationMap.insert({ L"FirebirdAim_Cluster_Shoot",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdAim_Cluster_Shoot"), 0, 8, 256, 256, 0.1f, false) });
	mAnimationMap.insert({ L"FirebirdVFX_ClusterBomb_Appear",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdVFX_ClusterBomb_Appear"), 0, 27, 256, 256, 0.08f, false) });
	mAnimationMap.insert({ L"FirebirdVFX_ClusterBomb_Explode",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdVFX_ClusterBomb_Explode"), 0, 12, 256, 256, 0.08f, false) });

	mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FirebirdAim_Cluster_Aim"));
	mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FirebirdAim_Cluster_Shoot"));
	mOwner->GetComponent<BoxCollider>()->SetEnable(false);
}

void FireBirdClusterAim::FixedUpdate()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	if (mCurrentTime < 3.f)
	{
		Vector2 dir = mPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

		float distance = dir.Magnitude();

		float forceMagnitude = 10.f + (distance * 2.f);
		forceMagnitude = clamp(forceMagnitude, 0, 80.f);

		Vector2 force = dir.Normalized() * forceMagnitude / 8.f;
		GetGameObject()->GetComponent<Rigidbody>()->AddForce(force);
	}

	else if(mCurrentTime >= 3.f)
	{
		GetGameObject()->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
	}
}

void FireBirdClusterAim::Update()
{
	if (!mIsShoot && mOwner->GetComponent<Animator>()->IsFinish())
	{
		mIsShoot = true;
		GetGameObject()->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FirebirdVFX_ClusterBomb_Appear"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FirebirdVFX_ClusterBomb_Explode"));
	}

	else if (mIsShoot && mOwner->GetComponent<Animator>()->IsFinish())
	{
		mOwner->Destroy();
	}
}

AnimationInfo* FireBirdClusterAim::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
}
