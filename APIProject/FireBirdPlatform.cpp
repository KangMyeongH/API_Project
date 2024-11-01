#include "pch.h"
#include "FireBirdPlatform.h"

#include "BoxCollider.h"
#include "FloatingBombObj.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "Player.h"
#include "State.h"
#include "StateMachine.h"
#include "TimeManager.h"

class Player;

FireBirdPlatform::~FireBirdPlatform()
{
	for (auto& ani : mAnimationMap)
	{
		delete ani.second;
	}
}

void FireBirdPlatform::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}

void FireBirdPlatform::Start()
{
	mOriginPosition = GetTransform()->GetWorldPosition();
	mAnimationMap.insert({ L"FireBird_PlatformA_Idle",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBird_PlatformA_Idle"), 0, 4, 304, 192, 0.07f, true) });
	mAnimationMap.insert({ L"FireBird_PlatformA_IdleWarning",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBird_PlatformA_IdleWarning"), 0, 4, 304, 192, 0.07f, true) });
	mAnimationMap.insert({ L"FireBird_PlatformA_IdleDoubleWarning",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBird_PlatformA_IdleDoubleWarning"), 0, 4, 304, 192, 0.07f, true) });
	mAnimationMap.insert({ L"FireBird_PlatformA_Damaged",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBird_PlatformA_Damaged"), 0, 4, 304, 192, 0.07f, false) });
	mAnimationMap.insert({ L"FireBird_PlatformA_DamagedWarning",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBird_PlatformA_DamagedWarning"), 0, 4, 304, 192, 0.07f, false) });
	mAnimationMap.insert({ L"FireBird_PlatformA_Destroy",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBird_PlatformA_Destroy"), 0, 2, 304, 192, 0.07f, false) });
	mAnimationMap.insert({ L"FireBird_PlatformA_Dead",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBird_PlatformA_Dead"), 0, 1, 304, 192, 0.07f, false) });
}

void FireBirdPlatform::FixedUpdate()
{
	Return2OriginPosition();
}

void FireBirdPlatform::Update()
{
	if (mHp > 0)
	{
		mReturnDelayTime += TimeManager::GetInstance().GetDeltaTime();
		if (mReturnDelayTime >= 6.f)
		{
			StartReturn();
		}
	}

	else if (mHp == 0)
	{
		mReturnDelayTime += TimeManager::GetInstance().GetDeltaTime();
		if (mReturnDelayTime >= 8.f)
		{
			Respawn();
			StartReturn();
			GetRandomStartPosition();
		}
	}
}

void FireBirdPlatform::OnCollisionEnter(Collision other)
{
	if (other.GetGameObject()->GetTag() == PLAYER)
	{
		if (other.GetGameObject()->GetComponent<Player>()->GetStateMachine()->GetCurrentState()->GetType() == CHARGEATTACK)
		{
			Damaged();
		}
	}

	if (other.GetGameObject()->GetTag() == BULLET)
	{
		Damaged();
	}
}

void FireBirdPlatform::Damaged()
{
	mReturnSpeed = 100.f;
	mReturnCurrentTime = 0;
	mReturnDelayTime = 0;
	mIsReturn = false;
	mHp--;

	if (mHp == 3)
	{
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_Damaged"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FireBird_PlatformA_Idle"));
	}

	if (mHp == 2)
	{
		// todo : hp = 2일때 이미지 출력
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_DamagedWarning"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FireBird_PlatformA_IdleWarning"));
	}

	else if (mHp == 1)
	{
		// todo : hp = 1일때 이미지 출력
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_DamagedWarning"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FireBird_PlatformA_IdleDoubleWarning"));
	}


	if (mHp <= 0)
	{
		// todo : 터지는로직
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_Destroy"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FireBird_PlatformA_Dead"));
		mOwner->GetComponent<SpriteRenderer>()->SetAngle(30);
		mOwner->GetComponent<BoxCollider>()->SetEnable(false);
		mOwner->GetComponent<Rigidbody>()->SetUseGravity(true);
		if (!mOwner->GetTransform()->GetChildren().empty())
		{
			mOwner->GetTransform()->GetChildren().front()->SetParent(nullptr);
		}
		GameObjectManager::GetInstance().AddGameObject<FloatingBombObj>()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	}
}

void FireBirdPlatform::Damaged(int damage)
{
	mReturnSpeed = 100.f;
	mReturnCurrentTime = 0;
	mReturnDelayTime = 0;
	mIsReturn = false;
	mHp -= damage;

	if (mHp == 3)
	{
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_Damaged"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FireBird_PlatformA_Idle"));
	}

	if (mHp == 2)
	{
		// todo : hp = 2일때 이미지 출력
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_DamagedWarning"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FireBird_PlatformA_IdleWarning"));
	}

	else if (mHp == 1)
	{
		// todo : hp = 1일때 이미지 출력
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_DamagedWarning"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FireBird_PlatformA_IdleDoubleWarning"));
	}


	if (mHp <= 0)
	{
		mHp = 0;
		// todo : 터지는로직
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_Destroy"));
		mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FireBird_PlatformA_Dead"));
		mOwner->GetComponent<SpriteRenderer>()->SetAngle(30);
		mOwner->GetComponent<BoxCollider>()->SetEnable(false);
		mOwner->GetComponent<Rigidbody>()->SetUseGravity(true);
		GameObjectManager::GetInstance().AddGameObject<FloatingBombObj>()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	}
}

void FireBirdPlatform::Respawn()
{
	mReturnSpeed = 600.f;
	mHp = 4;
	mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBird_PlatformA_Idle"));
	mOwner->GetComponent<SpriteRenderer>()->SetAngle(0);
	mOwner->GetComponent<BoxCollider>()->SetEnable(true);
	mOwner->GetComponent<Rigidbody>()->SetUseGravity(false);
}

void FireBirdPlatform::Return2OriginPosition()
{
	if (mIsReturn && mHp > 0)
	{
		mReturnCurrentTime += TimeManager::GetInstance().GetDeltaTime();

		if (mReturnCurrentTime >= mReturnDurationTime)
		{
			mReturnCurrentTime = mReturnDurationTime;
			mIsReturn = false;
		}

		mOwner->GetTransform()->SetWorldPosition(Vector2::Lerp(mReturnStartPosition, mOriginPosition, mReturnCurrentTime / mReturnDurationTime));
	}
}

void FireBirdPlatform::StartReturn()
{
	if (mIsReturn == false && mHp > 0)
	{
		mIsReturn = true;
		mReturnStartPosition = mOwner->GetTransform()->GetWorldPosition();

		Vector2 direction = mOriginPosition - mReturnStartPosition;
		float length = direction.Magnitude();

		if (length <= FLT_EPSILON)
		{
			mIsReturn = false;
			return;
		}
		mReturnDurationTime = length / mReturnSpeed;
	}
}

void FireBirdPlatform::GetRandomStartPosition()
{
	int side = rand() % 4;
	switch (side)
	{
	case 0:
		mReturnStartPosition = Vector2({ static_cast<float>(rand() % 2800), -50.f });
		break;
	case 1: 
		mReturnStartPosition = Vector2(2800.f + 50.f, static_cast<float>(rand() % 1600));
		break;
	case 2: 
		mReturnStartPosition = Vector2(static_cast<float>(rand() % 2800), 1600.f + 50.f);
		break;
	case 3: 
		mReturnStartPosition = Vector2(-50.f, static_cast<float>(rand() % 1600));
		break;
	}
}

AnimationInfo* FireBirdPlatform::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
}
