#include "pch.h"
#include "FireBird.h"

#include "GameObjectManager.h"
#include "ImageManager.h"

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
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();

	// 몸통
	mAnimationMap.insert({ L"BOSS_Firebird_Body_Idle",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Body_Idle"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Body_Idle",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Body_Idle"), 0, 4, 1320, 400, 0.8f, true) });

	// 날개
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_DownLoop01",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_DownLoop01"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_DownLoop02",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_DownLoop02"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_DownLoop03",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_DownLoop03"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_DownLoop04",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_DownLoop04"), 0, 4, 1320, 400, 0.8f, true) });

	mAnimationMap.insert({ L"BOSS_Firebird_Wing_UpLoop01",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_UpLoop01"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_UpLoop02",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_UpLoop02"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_UpLoop03",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_UpLoop03"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_Firebird_Wing_UpLoop04",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_UpLoop04"), 0, 4, 1320, 400, 0.8f, true) });

	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_DownLoop01",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_DownLoop01"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_DownLoop02",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_DownLoop02"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_DownLoop03",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_DownLoop03"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_DownLoop04",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_DownLoop04"), 0, 4, 1320, 400, 0.8f, true) });

	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_UpLoop01",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_UpLoop01"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_UpLoop02",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_UpLoop02"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_UpLoop03",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_UpLoop03"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_UpLoop04",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_UpLoop04"), 0, 4, 1320, 400, 0.8f, true) });

	mAnimationMap.insert({ L"BOSS_Firebird_Wing_NeuLoop",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_Firebird_Wing_NeuLoop"), 0, 4, 1320, 400, 0.8f, true) });
	mAnimationMap.insert({ L"BOSS_FirebirdBroken_Wing_NeuLoop",new AnimationInfo(ImageManager::GetInstance().FindImage(L"BOSS_FirebirdBroken_Wing_NeuLoop"), 0, 4, 1320, 400, 0.8f, true) });

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

		break;
	case BODY_ATTACK:

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
		break;
	case BOMBER:
		break;
	case BEHIND_FIRE:
		break;
	case BODY_ATTACK:
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

void FireBird::Debug(ID2D1HwndRenderTarget* render)
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

}

void FireBird::BomberPattern()
{
}

void FireBird::BehindFirePattern()
{
}

void FireBird::BodyAttackPattern()
{
}

void FireBird::ReturnPattern()
{
	if (GetGameObject()->GetComponent<Rigidbody>()->GetVelocity().y > 0)
	{
		if (GetTransform()->GetWorldPosition().y >= 800.f)
		{
			mPattern = BOMBER;
		}
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


	mWing->GetComponent<Animator>()->MotionChange(mWingAnimation[index]);
}

