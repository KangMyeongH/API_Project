#include "pch.h"
#include "FireBirdAim.h"

#include "BoxCollider.h"
#include "Effect.h"
#include "EffectObj.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "TimeManager.h"

void FireBirdAim::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}

void FireBirdAim::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();
	GetTransform()->SetWorldPosition(mPlayer->GetTransform()->GetWorldPosition());

	mAnimationMap.insert({ L"FirebirdAim_Incendiary_Appear",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdAim_Incendiary_Appear"), 0, 5, 256, 256, 0.2f, false) });
	mAnimationMap.insert({ L"FirebirdAim_Incendiary_Aim",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdAim_Incendiary_Aim"), 0, 23, 256, 256, 0.2f, false) });
	mAnimationMap.insert({ L"FirebirdAim_Incendiary_AttackLoop",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdAim_Incendiary_AttackLoop"), 0, 6, 256, 256, 0.08f, true) });
	mAnimationMap.insert({ L"FirebirdVFX_ShootExplode",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdVFX_ShootExplode"), 0, 14, 256, 256, 0.08f, false) });


	mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FirebirdAim_Incendiary_Appear"));
	mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FirebirdAim_Incendiary_Aim"));
	mOwner->GetComponent<BoxCollider>()->SetEnable(false);
}

void FireBirdAim::FixedUpdate()
{
	Vector2 dir = mPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

	float distance = dir.Magnitude();

	float forceMagnitude = 10.f + (distance * 2.f);
	forceMagnitude = clamp(forceMagnitude, 0, 80.f);

	Vector2 force = dir.Normalized() * forceMagnitude / 8.f;
	GetGameObject()->GetComponent<Rigidbody>()->AddForce(force);
}

void FireBirdAim::Update()
{
	if (mOwner->GetComponent<Animator>()->IsFinish())
	{
		mIsShoot = true;
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FirebirdAim_Incendiary_AttackLoop"));
	}

	if (mIsShoot)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= mDurationTime)
		{
			mCurrentTime = 0;
			GameObjectManager::GetInstance().AddGameObject<EffectObj>()->GetComponent<Effect>()->SetEffect(GetTransform()->GetWorldPosition(), FindAniInfo(L"FirebirdVFX_ShootExplode"));
			mOwner->GetComponent<BoxCollider>()->SetEnable(true);
		}

		else
		{
			mOwner->GetComponent<BoxCollider>()->SetEnable(false);
		}
	}
}

void FireBirdAim::OnEnable()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();
	GetTransform()->SetWorldPosition(mPlayer->GetTransform()->GetWorldPosition());
	mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FirebirdAim_Incendiary_Appear"));
	mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FirebirdAim_Incendiary_Aim"));
	mOwner->GetComponent<BoxCollider>()->SetEnable(false);
	mIsShoot = false;
	mCurrentTime = 0;
	mOwner->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
}

void FireBirdAim::OnDisable()
{

}

AnimationInfo* FireBirdAim::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
}


