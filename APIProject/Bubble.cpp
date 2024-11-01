#include "pch.h"
#include "Bubble.h"

#include "BubbleLeft.h"
#include "BubbleRight.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SoundMgr.h"
#include "TextRenderer.h"
#include "TimeManager.h"

void Bubble::Awake()
{
	mUpdateType = UPDATE;
}

void Bubble::Start()
{
	mOffset = { 0.f ,0.f }; // -36.5
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Bubble_Body.png", L"Bubble");
	mScale = { mTextLength * 13.f,22.f };
	mOwner->AddComponent<SpriteRenderer>(ImageManager::GetInstance().FindImage(L"Bubble"), 29.f, 22.f, 7);
	mOwner->GetComponent<SpriteRenderer>()->SetXScale(mTextLength / 2.f);
	mOwner->GetComponent<SpriteRenderer>()->SetFrame(0);

	mOwner->AddComponent<TextRenderer>(8, mOffset, mScale, mColor, mText, L"LiberationSans", 13.f);
	//mOwner->GetComponent<TextRenderer>()->SetCenter(true);
	mOwner->GetComponent<TextRenderer>()->SetIndex(mTextLength);
	mLeft = GameObjectManager::GetInstance().AddGameObject<BubbleLeft>();
	mLeft->GetTransform()->SetWorldPosition({ GetTransform()->GetWorldPosition().x - (14.5f * mTextLength / 2.f),GetTransform()->GetWorldPosition().y });
	mLeft->GetComponent<SpriteRenderer>()->SetFrame(0);

	mRight = GameObjectManager::GetInstance().AddGameObject<BubbleRight>();
	mRight->GetTransform()->SetWorldPosition({ GetTransform()->GetWorldPosition().x + (14.5f * mTextLength / 2.f),GetTransform()->GetWorldPosition().y });
	mRight->GetComponent<SpriteRenderer>()->SetFrame(0);
}

void Bubble::Update()
{
	if (mTextLength < 0)
	{
		if (KeyManager::Get_Instance()->Key_Pressing('E'))
		{
			mOwner->Destroy();
			mLeft->Destroy();
			mRight->Destroy();
		}
	}

	mCurrentTime += TimeManager::GetInstance().GetDeltaTime() * mTimeScale;
	if (mCurrentTime >= .2f)
	{
		mTextLength--;
		mCurrentTime = 0;
		if (mTextLength >= 0)
		{
			mOwner->GetComponent<TextRenderer>()->SetIndex(mTextLength);
			CSoundMgr::Get_Instance()->StopSound(SOUND_TEXT);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_Text_Player.wav", SOUND_TEXT, gEffectVolume);
		}
	}
}
