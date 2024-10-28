#include "pch.h"
#include "FireBirdBomb.h"

#include "BoxCollider.h"
#include "FireBird.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "SoundMgr.h"

FireBirdBomb::~FireBirdBomb()
{
	for (auto& ani : mAnimationMap)
	{
		delete ani.second;
	}
}

void FireBirdBomb::Awake()
{
	mUpdateType = UPDATE;
	mAnimationMap.insert({ L"FireBirdVFX_Bomb_Appear",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBirdVFX_Bomb_Appear"), 0, 4, 256, 256, 0.08f, false) });
	mAnimationMap.insert({ L"FireBirdVFX_Bomb_Explode",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBirdVFX_Bomb_Explode"), 0, 12, 256, 256, 0.2f, false) });
	mAnimationMap.insert({ L"FirebirdVFX_Bomb_Falling",new AnimationInfo(ImageManager::GetInstance().FindImage(L"FirebirdVFX_Bomb_Falling"), 0, 4, 256, 256, 0.2f, true) });
}

void FireBirdBomb::Start()
{
	GameObjectManager::GetInstance().GetGameObjectsForTag(BOSS)->front()->GetComponent<FireBird>()->SetBomb(this);
	Pending();
	GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBirdVFX_Bomb_Appear"));
	GetGameObject()->GetComponent<Animator>()->Pause(true);
}

void FireBirdBomb::Update()
{
	if (mIsFire)
	{
		if (GetGameObject()->GetComponent<Animator>()->IsFinish())
		{
			GetGameObject()->GetComponent<Rigidbody>()->SetUseGravity(true);
			GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FirebirdVFX_Bomb_Falling"));
		}
	}

	else if (mIsBoom)
	{
		if (GetGameObject()->GetComponent<Animator>()->IsFinish())
		{
			Pending();
		}
	}

	if (GetTransform()->GetWorldPosition().y >= 1800.f)
	{
		Pending();
	}
}

void FireBirdBomb::OnCollisionEnter(Collision other)
{
	if (other.GetGameObject()->GetTag() == PLAYER || other.GetGameObject()->GetTag() == PLATFORM)
	{
		Boom();
	}
}

void FireBirdBomb::Pending()
{
	mIsFire = false;
	mIsBoom = false;
	GetGameObject()->GetComponent<Animator>()->Pause(true);
	GetTransform()->SetWorldPosition({ 5000.f,-5000.f });
	GetGameObject()->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
	GetGameObject()->GetComponent<BoxCollider>()->SetEnable(false);
	GetGameObject()->GetComponent<Rigidbody>()->SetUseGravity(false);
}

void FireBirdBomb::Fire(Vector2 position)
{
	if (mIsFire) return;
	mIsFire = true;
	mIsBoom = false;
	CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BombingStart.wav", SOUND_BOSS_EFFECT, gEffectVolume);

	GetTransform()->SetWorldPosition(position);
	GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBirdVFX_Bomb_Appear"));
	GetGameObject()->GetComponent<Animator>()->Pause(false);
	GetGameObject()->GetComponent<BoxCollider>()->SetEnable(true);
}

void FireBirdBomb::Boom()
{
	mIsFire = false;
	mIsBoom = true;
	CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BombingBombExplosion.wav", SOUND_BOSS_EFFECT, gEffectVolume);

	GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"FireBirdVFX_Bomb_Explode"));
	GetGameObject()->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
	GetGameObject()->GetComponent<BoxCollider>()->SetEnable(false);
	GetGameObject()->GetComponent<Rigidbody>()->SetUseGravity(false);
}

AnimationInfo* FireBirdBomb::FindAniInfo(const TCHAR* key)
{
	
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
	
}
