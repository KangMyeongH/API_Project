#include "pch.h"
#include "FireBird.h"

#include "FireBirdAimObj.h"
#include "FireBirdBodyVFXObj.h"
#include "FireBirdBomb.h"
#include "FireBirdClusterAimObj.h"
#include "FireBirdPlatform.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "SoundMgr.h"
#include "TimeManager.h"

FireBird::~FireBird()
{
	for (auto& ani : mAnimationMap)
	{
		delete ani.second;
	}
}

void FireBird::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}

void FireBird::Start()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_Appear.wav", SOUND_BOSS, gEffectVolume);

	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();

	// 몸통
	mAnimationMap.insert({ L"BOSS_Firebird_Body_Idle",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Body_Idle"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Body_Idle",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Body_Idle"), 0, 4, 1320, 400, 0.8f, true) });

	// 날개
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_DownLoop01",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_DownLoop01"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_DownLoop02",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_DownLoop02"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_DownLoop03",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_DownLoop03"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_DownLoop04",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_DownLoop04"), 0, 4, 1320, 400, 0.03f, true) });

	mAnimationMap.insert({ L"BOSS_Firebird_Wing_UpLoop01",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_UpLoop01"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_UpLoop02",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_UpLoop02"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_UpLoop03",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_UpLoop03"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_UpLoop04",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_UpLoop04"), 0, 4, 1320, 400, 0.8f, true) });

	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_DownLoop01",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_DownLoop01"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_DownLoop02",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_DownLoop02"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_DownLoop03",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_DownLoop03"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_DownLoop04",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_DownLoop04"), 0, 4, 1320, 400, 0.03f, true) });

	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_UpLoop01",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_UpLoop01"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_UpLoop02",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_UpLoop02"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_UpLoop03",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_UpLoop03"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_UpLoop04",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_UpLoop04"), 0, 4, 1320, 400, 0.8f, true) });

	mAnimationMap.insert({ L"BOSS_Firebird_Wing_NeuLoop",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_NeuLoop"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_NeuLoop",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_NeuLoop"), 0, 4, 1320, 400, 0.8f, true) });

	mAnimationMap.insert({ L"BOSS_BehindFirebird_Idle",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_BehindFirebird_Idle"), 0, 1, 396, 126, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_BehindFirebird_Shoot",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_BehindFirebird_Shoot"), 0, 11, 396, 126, 0.08f, false) });

	mAnimationMap.insert({ L"Firebird_Body_BodySlapLoop",new AnimationInfo(ImageManager::GetInstance().FindImage(L"Firebird_Body_BodySlapLoop"), 0, 1, 933, 445, 0.08f, true) });


	mWingAnimation[0] = FindAniInfo(L"BOSS_Firebird_Wing_UpLoop04");
	mWingAnimation[1] = FindAniInfo(L"BOSS_Firebird_Wing_UpLoop03");
	mWingAnimation[2] = FindAniInfo(L"BOSS_Firebird_Wing_UpLoop02");
	mWingAnimation[3] = FindAniInfo(L"BOSS_Firebird_Wing_UpLoop01");
	mWingAnimation[4] = FindAniInfo(L"BOSS_Firebird_Wing_NeuLoop");
	mWingAnimation[5] = FindAniInfo(L"BOSS_Firebird_Wing_DownLoop01");
	mWingAnimation[6] = FindAniInfo(L"BOSS_Firebird_Wing_DownLoop02");
	mWingAnimation[7] = FindAniInfo(L"BOSS_Firebird_Wing_DownLoop03");
	mWingAnimation[8] = FindAniInfo(L"BOSS_Firebird_Wing_DownLoop04");

	mBrokenWingAnimation[0] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_UpLoop04");
	mBrokenWingAnimation[1] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_UpLoop03");
	mBrokenWingAnimation[2] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_UpLoop02");
	mBrokenWingAnimation[3] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_UpLoop01");
	mBrokenWingAnimation[4] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_NeuLoop");
	mBrokenWingAnimation[5] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_DownLoop01");
	mBrokenWingAnimation[6] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_DownLoop02");
	mBrokenWingAnimation[7] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_DownLoop03");
	mBrokenWingAnimation[8] = FindAniInfo(L"BOSS_FirebirdBroken_Wing_DownLoop04");


	GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"BOSS_Firebird_Body_Idle"));
}

void FireBird::FixedUpdate()
{
	Vector2 dir = {};
	switch (mPattern)
	{
	case SHOOT:
	{
		dir = mPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

		float distance = dir.Magnitude();

		float forceMagnitude = mBaseForce + (distance * mForceFactor);
		forceMagnitude = clamp(forceMagnitude, 0, mMaxForce);

		Vector2 force = dir.Normalized() * forceMagnitude / 10.f;
		mAngle = force;
		GetGameObject()->GetComponent<Rigidbody>()->AddForce(force);
	}
		break;
	case BOMBER:
	{
		Vector2 bomberPosition = { mPlayer->GetTransform()->GetWorldPosition().x, 150.f };
		dir = bomberPosition - GetTransform()->GetWorldPosition();

		float distance = dir.Magnitude();

		float forceMagnitude = mBaseForce + (distance * mForceFactor);
		forceMagnitude = clamp(forceMagnitude, 0, mMaxForce);

		Vector2 force = dir.Normalized() * forceMagnitude / 10.f;
		mAngle = force;
		GetGameObject()->GetComponent<Rigidbody>()->AddForce(force);
	}
		break;
	case BEHIND_FIRE:
	{
		dir = mTargetPosition - GetTransform()->GetWorldPosition();

		float distance = dir.Magnitude();

		float forceMagnitude = mBaseForce + (distance * mForceFactor);
		forceMagnitude = clamp(forceMagnitude, 0, mMaxForce);
		Vector2 force;
			if(mReadyBehind) force = dir.Normalized() * forceMagnitude / 25.f;
			else if(!mReadyBehind) force = dir.Normalized() * forceMagnitude / 10.f;
		mAngle = force;
		GetGameObject()->GetComponent<Rigidbody>()->AddForce(force);
	}
		break;
	case BODY_ATTACK:
		{
			if (!mReadyBehind)
			{
				dir = mTargetPosition - GetTransform()->GetWorldPosition();

				float distance = dir.Magnitude();

				float forceMagnitude = mBaseForce + (distance * mForceFactor);
				forceMagnitude = clamp(forceMagnitude, 0, mMaxForce);
				Vector2 force;
				if (!mReadyBehind) force = dir.Normalized() * forceMagnitude / 10.f;
				mAngle = force;
				GetGameObject()->GetComponent<Rigidbody>()->AddForce(force);
			}

			else if (mReadyBodyAttack)
			{
				GetGameObject()->GetTransform()->Translate({ 35.f, 0 });
			}
		}

		break;
	case RETURN:
	{
		dir = Vector2{ 1400.f,800.f } - GetTransform()->GetWorldPosition();

		float distance = dir.Magnitude();

		float forceMagnitude = mBaseForce + (distance * mForceFactor);
		forceMagnitude = clamp(forceMagnitude, 0, mMaxForce);

		Vector2 force = dir.Normalized() * forceMagnitude / 10.f;
		mAngle = force;
		GetGameObject()->GetComponent<Rigidbody>()->AddForce(force);
	}
		break;
	default: 
		break;
	}

}

void FireBird::Update()
{
	switch (mPattern)
	{
	case SHOOT:
		ShootPattern();
		break;
	case BOMBER:
		BomberPattern();
		break;
	case BEHIND_FIRE:
		BehindFirePattern();
		break;
	case BODY_ATTACK:
		BodyAttackPattern();
		break;
	case RETURN:
		ReturnPattern();
		break;
	}

	float xAngle = clamp(mAngle.x / 3.f, -mMaxAngle, mMaxAngle);
	GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(xAngle);
	mWing->GetComponent<SpriteRenderer>()->SetAngle(xAngle);
	ChangeWingIndex();
}

void FireBird::OnCollisionEnter(Collision other)
{
	if (mReadyBodyAttack && other.GetGameObject()->CompareTag(PLATFORM))
	{
		other.GetGameObject()->GetComponent<FireBirdPlatform>()->Damaged(3);
	}
}

void FireBird::Debug(ID2D1DeviceContext* render)
{
	// 텍스트 서식 설정
	IDWriteTextFormat* textFormat = nullptr;
	ID2D1SolidColorBrush* brush = nullptr;

	gWriteFactory->CreateTextFormat(
		L"Arial",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"en-us",
		&textFormat
	);
	render->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);

	// 출력할 영역 설정
	D2D1_RECT_F layoutRect = D2D1::RectF(10, 10, 400, 100);


	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);

	wchar_t array[32];
	swprintf_s(array, 32, L"%f, %f", mAngle.x, mAngle.y);

	// 텍스트를 그리기
	render->DrawText(
		array,
		wcslen(array),
		textFormat,
		layoutRect,
		brush
	);

	textFormat->Release();
}

AnimationInfo* FireBird::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
}

void FireBird::ShootPattern()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	if (mCurrentTime >= 8.f)
	{
		SetRandomPattern();
	}
}

void FireBird::BomberPattern()
{
	if (GetTransform()->GetWorldPosition().y <= 150.f)
	{
		float offset = 150.f;
		GetGameObject()->GetComponent<Rigidbody>()->SetVelocity({ GetGameObject()->GetComponent<Rigidbody>()->GetVelocity().x,0 });
		mBombCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mBombCurrentTime >= mBombDelay)
		{
			mBombCurrentTime = 0;
			if(mBombIndex == 8)
			{
				SetRandomPattern();
				mBombIndex = 0;
				return;
			}
			mBomb[mBombIndex]->Fire({ GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y + offset });
			mBombIndex++;
		}
	}
}

void FireBird::BehindFirePattern()
{
	if (GetTransform()->GetWorldPosition().y >= 2000.f && !mReadyBehind)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
		CSoundMgr::Get_Instance()->PlayLoopSound(L"SFX_Chap4_Firebird_BackLoop.wav", SOUND_BOSS, gEffectVolume);
		GetTransform()->SetWorldPosition({ mPlayer->GetTransform()->GetWorldPosition().x, -1000.f });
		mTargetPosition = { mPlayer->GetTransform()->GetWorldPosition().x, 475.f };
		GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"BOSS_BehindFirebird_Idle"));
		mWing->GetComponent<SpriteRenderer>()->SetEnable(false);
		mWing->GetComponent<Animator>()->SetEnable(false);
		mReadyBehind = true;
	}

	else if(GetTransform()->GetWorldPosition().y <= -500.f && mOwner->GetComponent<Rigidbody>()->GetVelocity().y < 0)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_Appear.wav", SOUND_BOSS, gEffectVolume);
		GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"BOSS_Firebird_Body_Idle"));
		mWing->GetComponent<SpriteRenderer>()->SetEnable(true);
		mWing->GetComponent<Animator>()->SetEnable(true);
		GetTransform()->SetWorldPosition({ 1400.f, 2000.f });
		GetGameObject()->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
		mPattern = RETURN;
	}

	if (mReadyBehind)
	{
		mTargetPosition = mPlayer->GetTransform()->GetWorldPosition();
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= 2.f && !mIsShoot)
		{
			mIsShoot = true;
			GameObjectManager::GetInstance().AddGameObject<FireBirdClusterAimObj>();
		}

		if (mCurrentTime >= 6.25f)
		{
			GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"BOSS_BehindFirebird_Shoot"));
			GetGameObject()->GetComponent<Animator>()->SetNextMotion(FindAniInfo(L"BOSS_BehindFirebird_Idle"));
			mIsShoot = false;
			mReadyBehind = false;
			mTargetPosition = { GetTransform()->GetWorldPosition().x, -600.f };
		}
	}
}

void FireBird::BodyAttackPattern()
{
	if (GetTransform()->GetWorldPosition().y >= 2000.f && !mReadyBehind)
	{
		mTargetPosition = { 3000.f, mPlayer->GetTransform()->GetWorldPosition().y };
		GetTransform()->SetWorldPosition({ -300.f, mPlayer->GetTransform()->GetWorldPosition().y });
		GameObjectManager::GetInstance().AddGameObject<FireBirdBodyVFXObj>();
		mWing->GetComponent<SpriteRenderer>()->SetEnable(false);
		mWing->GetComponent<Animator>()->SetEnable(false);
		GetGameObject()->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
		GetGameObject()->GetComponent<Rigidbody>()->SetUseGravity(false);
		mReadyBehind = true;
	}

	else if (mReadyBehind && !mReadyBodyAttack)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= 1.6f)
		{
			GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"Firebird_Body_BodySlapLoop"));
			CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BodySlap.wav", SOUND_BOSS, gEffectVolume);

			mReadyBehind = false;
			mReadyBodyAttack = true;
		}
	}

	else if (mReadyBodyAttack && GetTransform()->GetWorldPosition().x > 3100.f)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_Appear.wav", SOUND_BOSS, gEffectVolume);
		GetGameObject()->GetComponent<Animator>()->MotionChange(FindAniInfo(L"BOSS_Firebird_Body_Idle"));
		mWing->GetComponent<SpriteRenderer>()->SetEnable(true);
		mWing->GetComponent<Animator>()->SetEnable(true);
		GetTransform()->SetWorldPosition({ 1400.f, 2000.f });
		GetGameObject()->GetComponent<Rigidbody>()->Velocity() = { 0,0 };
		mReadyBehind = false;
		mReadyBodyAttack = false;
		mPattern = RETURN;
	}
}

void FireBird::ReturnPattern()
{
	if (GetGameObject()->GetComponent<Rigidbody>()->GetVelocity().y > 0)
	{
		if (GetTransform()->GetWorldPosition().y >= 800.f)
		{
			SetRandomPattern();
		}
	}
}

void FireBird::GoToBottom()
{
	if (GetTransform()->GetWorldPosition().y >= 2000.f)
	{
		
	}
}

void FireBird::ChangeWingIndex()
{
	int index = 4;
	if (mAngle.y < -6.5f) 								index = 0;
	else if (-6.5f <= mAngle.y && mAngle.y < -4.5f) 	index = 1;
	else if (-4.5f <= mAngle.y && mAngle.y < -3.f) 		index = 2;
	else if (-3.f <= mAngle.y && mAngle.y < -1.f) 		index = 3;
	else if (-1.f <= mAngle.y && mAngle.y < 1.f) 		index = 4;
	else if (1.f <= mAngle.y && mAngle.y < 3.f) 		index = 5;
	else if (3.f <= mAngle.y && mAngle.y < 4.5f) 		index = 6;
	else if (4.5f <= mAngle.y && mAngle.y < 6.5f) 		index = 7;
	else if (6.5f <= mAngle.y) 							index = 8;

	if (index != mWingIndex)
	{
		mWingIndex = index;
		mWing->GetComponent<Animator>()->MotionChange(mWingAnimation[mWingIndex]);
	}
}

void FireBird::SetRandomPattern()
{
	int index = rand() % 4;
	switch (index)
	{
	case 0:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
		CSoundMgr::Get_Instance()->PlayLoopSound(L"SFX_Chap4_Firebird_Loop.wav", SOUND_BOSS, gEffectVolume);
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_Minigun_Start.wav", SOUND_BOSS_EFFECT, gEffectVolume);
		mPattern = SHOOT;
		GameObjectManager::GetInstance().AddGameObject<FireBirdAimObj>();
		mCurrentTime = 0;
		break;
	case 1:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
		CSoundMgr::Get_Instance()->PlayLoopSound(L"SFX_Chap4_Firebird_Loop.wav", SOUND_BOSS, gEffectVolume);
		mPattern = BOMBER;
		break;
	case 2:
		mPattern = BEHIND_FIRE;
		mTargetPosition = { 1400.f,2000.f };
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_Disappear.wav", SOUND_BOSS, gEffectVolume);
		mCurrentTime = 0;
		break;
	case 3:
		mPattern = BODY_ATTACK;
		mTargetPosition = { 1400.f,2000.f };
		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_Disappear.wav", SOUND_BOSS, gEffectVolume);
		mCurrentTime = 0;
		mReadyBehind = false;
		mReadyBodyAttack = false;
		break;
	}
}

void FireBird::SetBomb(FireBirdBomb* bomb)
{
	for (auto& obj : mBomb)
	{
		if (obj == nullptr)
		{
			obj = bomb;
			break;
		}
	}
}

