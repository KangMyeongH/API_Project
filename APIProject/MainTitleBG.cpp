#include "pch.h"
#include "MainTitleBG.h"

#include "AnimationCurve.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "MainSceneBGObj.h"
#include "MainTitleButton.h"
#include "MainTitleButtonObj.h"
#include "SNBLogoObj.h"
#include "SoundMgr.h"
#include "TimeManager.h"
#include "Transform.h"

void MainTitleBG::Awake()
{
	mUpdateType = UPDATE;
	mStartPosition = { -300.f,270.f };
}

void MainTitleBG::Update()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	if (mCurrentTime >= 9.0f)
	{
		mCurrentTime = 9.0f;
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_TitleLightOn.wav", SOUND_EFFECT, 1.f);
		mOwner->GetComponent<SpriteRenderer>()->ChangeSprite(ImageManager::GetInstance().FindImage(L"Spr_MainTitle_LightOn"), 1920.f, 1080.f, 2);
		mBlueLedFinish = true;
		GameObjectManager::GetInstance().AddGameObject<MainSceneBGObj>();
		GameObjectManager::GetInstance().AddGameObject<MainTitleButtonObj>()->GetComponent<MainTitleButton>()->SetButton(GAME_START);
		GameObjectManager::GetInstance().AddGameObject<MainTitleButtonObj>()->GetComponent<MainTitleButton>()->SetButton(SPEED_RUN);
		GameObjectManager::GetInstance().AddGameObject<MainTitleButtonObj>()->GetComponent<MainTitleButton>()->SetButton(SETTING);
		GameObjectManager::GetInstance().AddGameObject<MainTitleButtonObj>()->GetComponent<MainTitleButton>()->SetButton(END_GAME);
		GameObjectManager::GetInstance().AddGameObject<SNBLogoObj>();

		SetEnable(false);
	}
	float t = mCurrentTime / 9.f;
	GetTransform()->SetWorldPosition(Vector2::Lerp(mStartPosition, { 960.f,540.f }, AnimationCurve::EaseOutSine(t)));
	mOwner->GetComponent<SpriteRenderer>()->SetFrame(0);
}
