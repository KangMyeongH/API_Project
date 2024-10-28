#include "pch.h"
#include "MainTitleButton.h"

#include "AnimationCurve.h"
#include "FireBirdScene.h"
#include "GameObject.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "SoundMgr.h"
#include "TextRenderer.h"
#include "TimeManager.h"
#include "TitleScene.h"
#include "Transform.h"

void MainTitleButton::Awake()
{
	mUpdateType = UPDATE;
}

void MainTitleButton::Start()
{
	Vector2 offset = { 20.f,12.5f };
	switch (mType)
	{
	case GAME_START:
		swprintf_s(mArray, 32, L"게임 시작");
		GetTransform()->SetWorldPosition({ 1705.f,664.f });
		break;
	case SPEED_RUN:
		swprintf_s(mArray, 32, L"스피드런 모드");
		GetTransform()->SetWorldPosition({ 1705.f,735.f });
		break;
	case SETTING:
		swprintf_s(mArray, 32, L"설정");
		GetTransform()->SetWorldPosition({ 1705.f,806.f });
		break;
	case END_GAME:
		swprintf_s(mArray, 32, L"게임 종료");
		GetTransform()->SetWorldPosition({ 1705.f,877.f });
		break;
	}
	mOwner->GetComponent<SpriteRenderer>()->SetFrame(0);
	mOwner->AddComponent<TextRenderer>(8, offset, GetTransform()->GetWorldScale(), mColor, mArray, L"LiberationSans", 28.f);
}

void MainTitleButton::Update()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	float t = mCurrentTime;
	if (t >= 1.f)
	{
		mCurrentTime = 1.f;
	}
	mOwner->GetComponent<SpriteRenderer>()->SetOpacity(AnimationCurve::Lerp(0.f, 1.f, t));
	mOpacity = AnimationCurve::Lerp(0.f, 0.8f, t);
	mOwner->GetComponent<TextRenderer>()->SetOpacity(mOpacity);
	mColor.a = mOpacity;
	if (mSelected && KeyManager::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		switch (mType)
		{
		case GAME_START:
			SceneManager::GetInstance().ChangeScene(new FireBirdScene);
			CSoundMgr::Get_Instance()->StopSound(SOUND_BUTTON_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_UI_Select.wav", SOUND_BUTTON_EFFECT, gEffectVolume);
			break;
		case SPEED_RUN:
			CSoundMgr::Get_Instance()->StopSound(SOUND_BUTTON_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_UI_Select.wav", SOUND_BUTTON_EFFECT, gEffectVolume);
			break;
		case SETTING:
			CSoundMgr::Get_Instance()->StopSound(SOUND_BUTTON_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_UI_Select.wav", SOUND_BUTTON_EFFECT, gEffectVolume);
			break;
		case END_GAME:
			CSoundMgr::Get_Instance()->StopSound(SOUND_BUTTON_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_UI_Select.wav", SOUND_BUTTON_EFFECT, gEffectVolume);
			PostQuitMessage(0);
			break;
		}
	}
}

void MainTitleButton::OnCollisionEnter(Collision other)
{
	GetTransform()->Translate({ -18.f,0 });
	mOwner->GetComponent<SpriteRenderer>()->ChangeSprite(ImageManager::GetInstance().FindImage(L"SelectBox_Selected"), 358.f, 61.f, 8);
	mOwner->GetComponent<SpriteRenderer>()->SetFrame(0);
	mColor = { 1.f, 1.f, 1.f, 1.f };
	mOwner->GetComponent<TextRenderer>()->SetColor(mColor);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BUTTON_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_UI_Hovering.wav", SOUND_BUTTON_EFFECT, gEffectVolume);
	mSelected = true;
}

void MainTitleButton::OnCollisionExit(Collision other)
{
	GetTransform()->Translate({ 18.f,0 });
	mOwner->GetComponent<SpriteRenderer>()->ChangeSprite(ImageManager::GetInstance().FindImage(L"SelectBox"), 358.f, 61.f, 8);
	mOwner->GetComponent<SpriteRenderer>()->SetFrame(0);
	mColor = { 0.f, 0.9725f, 1.f, 0.8f };
	mOwner->GetComponent<TextRenderer>()->SetColor(mColor);
	mSelected = false;
}