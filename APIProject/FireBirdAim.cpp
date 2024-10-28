#include "pch.h"
#include "FireBirdAim.h"

#include "BoxCollider.h"
#include "Effect.h"
#include "EffectObj.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "SoundMgr.h"
#include "TimeManager.h"

FireBirdAim::~FireBirdAim()
{
	for (auto& ani : mAnimationMap)
	{
		delete ani.second;
	}
}

void FireBirdAim::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}

void FireBirdAim::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();
	GetTransform()->SetWorldPosition(mPlayer->GetTransform()->GetWorldPosition());

	mAnimationMap.insert({ L"FirebirdAim_Incendiary_Appear",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdAim_Incendiary_Appear"), 0, 5, 256, 256, 0.2f, false) });
	mAnimationMap.insert({ L"FirebirdAim_Incendiary_Aim",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdAim_Incendiary_Aim"), 0, 23, 256, 256, 0.08f, false) });
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

	mDurationCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	if (mDurationCurrentTime >= 8.f)
	{
		mOwner->Destroy();
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_Minigun_End.wav", SOUND_BOSS_EFFECT, gEffectVolume);
		return;
	}

	if (mIsShoot)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= mDurationTime)
		{
			int index = rand() % 5;

			switch (index)
			{
			case 0:
				CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"SFX_Ene_Turret_Shot (1).wav", SOUND_BOSS_EFFECT, gEffectVolume);
				break;
			case 1:
				CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"SFX_Ene_Turret_Shot (2).wav", SOUND_BOSS_EFFECT, gEffectVolume);
				break;
			case 2:
				CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"SFX_Ene_Turret_Shot (3).wav", SOUND_BOSS_EFFECT, gEffectVolume);
				break;
			case 3:
				CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"SFX_Ene_Turret_Shot (4).wav", SOUND_BOSS_EFFECT, gEffectVolume);
				break;
			case 4:
				CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"SFX_Ene_Turret_Shot (5).wav", SOUND_BOSS_EFFECT, gEffectVolume);
				break;

			}
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
	//mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FirebirdAim_Incendiary_Appear"));
	//mOwner->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"FirebirdAim_Incendiary_Aim"));
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


