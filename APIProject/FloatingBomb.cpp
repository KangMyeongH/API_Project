#include "pch.h"
#include "FloatingBomb.h"

#include "GameObject.h"
#include "ImageManager.h"

void FloatingBomb::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);

	int index = rand() % 4;
	switch (index)
	{
	case 0:
		mDir = { 0.5f, 0.5f }; // 오른쪽 아래 방향
		break;
	case 1:
		mDir = { 0.5f, -0.5f }; // 오른쪽 위 방향
		break;
	case 2:
		mDir = { -0.5f, 0.5f }; // 왼쪽 아래 방향
		break;
	case 3:
		mDir = { -0.5f, -0.5f }; // 왼쪽 위 방향
		break;
	}

	// 이동 속도
	mSpeed = 3.f;
}

void FloatingBomb::Start()
{
	mAnimationMap.insert({ L"FloatingBomb_Excholded_Back_lp", new AnimationInfo(ImageManager::GetInstance().FindImage(L"FloatingBomb_Excholded_Back_lp"), 0, 11, 256, 256, 0.08f, true) });
	mAnimationMap.insert({ L"FloatingBomb_Excholded_Front_lp", new AnimationInfo(ImageManager::GetInstance().FindImage(L"FloatingBomb_Excholded_Front_lp"), 0, 11, 256, 256, 0.08f, true) });
	mAnimationMap.insert({ L"FloatingBomb_Excholded_Neu_lp", new AnimationInfo(ImageManager::GetInstance().FindImage(L"FloatingBomb_Excholded_Neu_lp"), 0, 11, 256, 256, 0.08f, true) });
	mAnimationMap.insert({ L"FloatingBomb_ExcholdedStart", new AnimationInfo(ImageManager::GetInstance().FindImage(L"FloatingBomb_ExcholdedStart"), 0, 11, 256, 256, 0.08f, false) });
	mAnimationMap.insert({ L"FloatingBomb_ExplodeHuge", new AnimationInfo(ImageManager::GetInstance().FindImage(L"FloatingBomb_ExplodeHuge"), 0, 21, 512, 512, 0.08f, false) });
	mAnimationMap.insert({ L"FloatingBomb_Idle_lp", new AnimationInfo(ImageManager::GetInstance().FindImage(L"FloatingBomb_Idle_lp"), 0, 22, 256, 256, 0.08f, true) });
	mAnimationMap.insert({ L"FloatingBomb_Knockback", new AnimationInfo(ImageManager::GetInstance().FindImage(L"FloatingBomb_Knockback"), 0, 16, 256, 256, 0.08f, false) });

	mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FloatingBomb_Idle_lp"));
}

void FloatingBomb::FixedUpdate()
{
	if (!GetTransform()->GetParent())
	{
		GetTransform()->Translate(mDir * mSpeed);

		if (GetTransform()->GetWorldPosition().x <= 0.f)
		{
			GetTransform()->SetWorldPosition({ 0, GetTransform()->GetWorldPosition().y });
			mDir.x *= -1;
		}

		else if (GetTransform()->GetWorldPosition().x >= mBoundary.x)
		{
			GetTransform()->SetWorldPosition({ mBoundary.x, GetTransform()->GetWorldPosition().y });
			mDir.x *= -1;
		}

		if (GetTransform()->GetWorldPosition().y <= 0.f)
		{
			GetTransform()->SetWorldPosition({ GetTransform()->GetWorldPosition().x, 0 });
			mDir.y *= -1;
		}

		else if (GetTransform()->GetWorldPosition().y >= mBoundary.y)
		{
			GetTransform()->SetWorldPosition({ GetTransform()->GetWorldPosition().x, mBoundary.y });
			mDir.y *= -1;
		}
	}
}

void FloatingBomb::Update()
{
	
}

void FloatingBomb::OnEnable()
{

}

void FloatingBomb::OnDisable()
{
	mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
	mOwner->GetComponent<Animator>()->SetEnable(false);
}

void FloatingBomb::OnCollisionEnter(Collision other)
{
	
}

AnimationInfo* FloatingBomb::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
}
