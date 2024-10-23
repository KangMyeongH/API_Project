#include "pch.h"
#include "Grab.h"

#include "BoxCollider.h"
#include "ExcDashState.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "Player.h"
#include "StateMachine.h"
#include "SwingState.h"
#include "TimeManager.h"
#include "Transform.h"

Grab::~Grab()
{
	for (auto& ani : mAnimationMap)
	{
		delete ani.second;
	}
}

void Grab::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}

void Grab::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front()->GetComponent<Player>();
	mPlayer->SetGrab(this);
	ImageManager::GetInstance().InsertBmp(L"./Sprite/03. SNBGrab/Spr_SNBGrab_Flying.png", L"Grab_Flying");

	mAnimationMap.insert({ L"Grab_Flying",new AnimationInfo(ImageManager::GetInstance().FindImage(L"Grab_Flying"), 0, 1, 25, 67, 0.2f, false) });
	mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"Grab_Flying"));
	mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
	mOwner->GetComponent<Animator>()->SetEnable(false);
	mOwner->GetComponent<BoxCollider>()->SetEnable(false);
}

void Grab::FixedUpdate()
{
	if (mIsShoot)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime > mTime)
		{
			mCurrentTime = mTime;
			if (mTarget->GetGameObject()->CompareTag(ENEMY))
			{
				mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
				mOwner->GetComponent<Animator>()->SetEnable(false);
				mOwner->GetComponent<BoxCollider>()->SetEnable(false);
				mPlayer->GetStateMachine()->ChangeState(mPlayer->ExcDash);
			}

			else if (mTarget->GetGameObject()->CompareTag(PLATFORM))
			{
				mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
				mOwner->GetComponent<Animator>()->SetEnable(false);
				mOwner->GetComponent<BoxCollider>()->SetEnable(false);
				mPlayer->GetStateMachine()->ChangeState(mPlayer->Swing);
			}
		}
		GetTransform()->SetWorldPosition(Vector2::Lerp(mStart, mTargetPosition, mCurrentTime / mTime));
	}
}

void Grab::OnCollisionEnter(Collision other)
{
}

void Grab::Shoot()
{
	if (!mIsShoot)
	{
		Camera::GetInstance().Shake(0.05f, 10.f);
		mOwner->GetComponent<SpriteRenderer>()->SetEnable(true);
		mOwner->GetComponent<Animator>()->SetEnable(true);
		mOwner->GetComponent<BoxCollider>()->SetEnable(true);
		mCurrentTime = 0;
		GetTransform()->SetWorldPosition(mPlayer->GetTransform()->GetWorldPosition());
		mStart = GetTransform()->GetWorldPosition();
		if (mPlayer->GetTarget())
		{
			mTarget = mPlayer->GetTarget()->GetTransform();
			mTargetPosition = mTarget->GetWorldPosition();
		}

		else if (mPlayer->GetTargetPlatform())
		{
			mTarget = mPlayer->GetTargetPlatform()->GetTransform();
			mTargetPosition = mPlayer->GetGrabPoint();
		}

		mOwner->GetComponent<SpriteRenderer>()->SetAngle(Vector2::GetAngle(mStart, mTargetPosition) + 90.f);
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"Grab_Flying"));
		mIsShoot = true;
	}
}

void Grab::Debug(ID2D1HwndRenderTarget* render)
{
	if (mIsShoot)
	{
		
	}
}

AnimationInfo* Grab::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
}
