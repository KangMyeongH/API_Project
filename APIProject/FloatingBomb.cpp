#include "pch.h"
#include "FloatingBomb.h"

#include "BoxCollider.h"
#include "Enemy.h"
#include "FireBird.h"
#include "GameObject.h"
#include "ImageManager.h"
#include "SoundMgr.h"
#include "TimeManager.h"

void FloatingBomb::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);

	// 이동 속도
	mSpeed = 300.f;

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

	mOwner->GetComponent<Rigidbody>()->Velocity() = mDir * mSpeed;
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
}

void FloatingBomb::Update()
{
	if (mIsExplode && mOwner->GetComponent<Animator>()->IsFinish())
	{
		mOwner->Destroy();
	}

	mDir = mOwner->GetComponent<Rigidbody>()->GetVelocity();

	if (!GetTransform()->GetParent())
	{
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

		mOwner->GetComponent<Rigidbody>()->Velocity() = mDir;
	}

	else
	{
		mOwner->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
	}
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
	if (other.GetGameObject()->CompareTag(PLATFORM))
	{
		CollisionDirection dir = CollisionManager::DetectBoxCollisionDir(*mOwner->GetComponent<BoxCollider>()->GetRect(), *other.GetCollider()->GetRect());
		if (dir & LEFT || dir & RIGHT)
		{
			mDir.x *= -1;
		}

		if (dir & TOP || dir & BOTTOM)
		{
			mDir.y *= -1;
		}

		mOwner->GetComponent<Rigidbody>()->Velocity() = mDir;
	}

	if (other.GetGameObject()->CompareTag(BOSS))
	{
		if (mOwner->GetComponent<Enemy>()->GetKnockBack())
		{
			Vector2 dir = (other.GetGameObject()->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition()).Normalized();
			other.GetGameObject()->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
			other.GetGameObject()->GetComponent<Rigidbody>()->AddForce(dir * 1000.f);
			mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FloatingBomb_ExplodeHuge"));
			mOwner->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
			mOwner->GetComponent<BoxCollider>()->SetEnable(false);
			other.GetGameObject()->GetComponent<FireBird>()->Damaged();
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Miniboss_FloatingBomb_Explosion.wav", SOUND_EFFECT, gEffectVolume);
			mIsExplode = true;
		}
	}
}

AnimationInfo* FloatingBomb::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
}
