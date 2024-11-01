#include "pch.h"
#include "PRLG.h"

#include "BoxCollider.h"
#include "Bubble.h"
#include "BubbleObj.h"
#include "EdgeCollider.h"
#include "GameObjectManager.h"
#include "GrabObject.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "Platform.h"
#include "PlatformObject.h"
#include "Player.h"
#include "PlayerObject.h"
#include "PotalObj.h"
#include "PrologueCloudObj.h"
#include "PrologueMapObj.h"
#include "PrologueSkyObj.h"
#include "SoundMgr.h"
#include "TimeManager.h"
#include "TutoObj.h"

void PRLG::Awake()
{
	mUpdateType = UPDATE;
	ImageManager::GetInstance().InsertBmp(L"./Sprite/SNB_Sleep.png", L"SNB_Sleep");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/SNB_Awake1.png", L"SNB_Awake1");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/SNB_Awake2.png", L"SNB_Awake2");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/SNB_StandUp.png", L"SNB_StandUp");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/PRLG_1_1.png", L"PRLG_1_1");

}

void PRLG::Update()
{
	Scene01();
}

void PRLG::Scene01()
{
	//Camera::GetInstance().SetZoom(2.f);
	if (mIndex == 0)
	{
		Camera::GetInstance().SetZoom(3.f);
		mOwner->GetTransform()->SetWorldPosition({ 960.f,540.f });
		mOwner->AddComponent<SpriteRenderer>(8);
		mOwner->AddComponent<Animator>()->SetSprite(mOwner->GetComponent<SpriteRenderer>());
		mOwner->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"PRLG_1_1"), 0, 5, 80, 80, .1f);
		mOwner->GetComponent<Animator>()->Loop(true);
		mOwner->GetComponent<SpriteRenderer>()->SetOpacity(0);

		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Event_Dream.wav", gBGMVolume);
		GameObject* script01 = GameObjectManager::GetInstance().AddGameObject<BubbleObj>();
		script01->GetTransform()->SetWorldPosition({ 935.f,515.f });
		script01->GetComponent<Bubble>()->InitText(L"......빠..");
		mIndex++;
	}

	else if (mIndex ==1 && mKeyDown == false)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= 1.f)
		{
			mCurrentTime = 1.f;
		}
		float temp = 0.f + (1.f - 0.f) * mCurrentTime;
		mOwner->GetComponent<SpriteRenderer>()->SetOpacity(temp);
	}

	else if (mIndex == 1 && mKeyDown == true)
	{
		GameObject* script01 = GameObjectManager::GetInstance().AddGameObject<BubbleObj>();
		script01->GetTransform()->SetWorldPosition({ 935.f,515.f });
		script01->GetComponent<Bubble>()->InitText(L"...아빠..");
		mIndex++;
		mKeyDown = false;
	}

	else if (mIndex == 2 && mKeyDown == true)
	{
		GameObject* script01 = GameObjectManager::GetInstance().AddGameObject<BubbleObj>();
		script01->GetTransform()->SetWorldPosition({ 935.f,515.f });
		script01->GetComponent<Bubble>()->InitText(L"아빠!!!");
		mIndex++;
		mKeyDown = false;
	}

	else if (mIndex == 3 && mKeyDown == true)
	{
		GameObject* script01 = GameObjectManager::GetInstance().AddGameObject<BubbleObj>();
		script01->GetTransform()->SetWorldPosition({ 935.f,515.f });
		script01->GetComponent<Bubble>()->InitText(L"끝까지 가는게 중요한 게 아니야!");
		script01->GetComponent<Bubble>()->SetTimeScale(2.f);
		mIndex++;
		mKeyDown = false;
	}

	else if (mIndex == 4 && mKeyDown == true)
	{
		GameObject* script01 = GameObjectManager::GetInstance().AddGameObject<BubbleObj>();
		script01->GetTransform()->SetWorldPosition({ 985.f,515.f });
		script01->GetComponent<Bubble>()->InitText(L"왜? 이번엔 아빠 괜찮지 않았니?");
		script01->GetComponent<Bubble>()->SetTimeScale(2.f);
		mIndex++;
		mKeyDown = false;
	}

	else if (mIndex == 5 && mKeyDown == true)
	{
		GameObject* script01 = GameObjectManager::GetInstance().AddGameObject<BubbleObj>();
		script01->GetTransform()->SetWorldPosition({ 985.f,515.f });
		script01->GetComponent<Bubble>()->InitText(L"아니였니?");
		script01->GetComponent<Bubble>()->SetTimeScale(2.f);
		mIndex++;
		mKeyDown = false;
	}

	else if (mIndex == 6 && mKeyDown == true)
	{
		GameObject* script01 = GameObjectManager::GetInstance().AddGameObject<BubbleObj>();
		script01->GetTransform()->SetWorldPosition({ 935.f,515.f });
		script01->GetComponent<Bubble>()->InitText(L"그게 중요한 게 아니야, 아빠. 이건 그런게 아니라구");
		script01->GetComponent<Bubble>()->SetTimeScale(2.f);
		mIndex++;
		mKeyDown = false;
	}

	else if (mIndex == 7 && mKeyDown == true)
	{
		GameObject* script01 = GameObjectManager::GetInstance().AddGameObject<BubbleObj>();
		script01->GetTransform()->SetWorldPosition({ 985.f,515.f });
		script01->GetComponent<Bubble>()->InitText(L"그러면?");
		script01->GetComponent<Bubble>()->SetTimeScale(2.f);
		mIndex++;
		mKeyDown = false;
	}

	else if (mIndex == 8 && mKeyDown == true)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSoundMgr::Get_Instance()->PlayBGM(L"AMB_PRLG1_Bird.wav", gBGMVolume);
		mIndex++;
		mKeyDown = false;
		GameObjectManager::GetInstance().AddGameObject<PrologueMapObj>();
		GameObjectManager::GetInstance().AddGameObject<GrabObject>();
		GameObject* player = GameObjectManager::GetInstance().AddGameObject<PlayerObject>();
		player->GetTransform()->SetWorldPosition({ 522.f, 3557.f });
		player->GetComponent<SpriteRenderer>()->SetEnable(false);
		player->GetComponent<Animator>()->SetEnable(false);
		mOwner->GetTransform()->SetWorldPosition({ 522.f, 3545.f });
		mOwner->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"SNB_Sleep"), 0, 8, 80, 80, .2f);
		mOwner->GetComponent<Animator>()->Loop(false);




		Camera::GetInstance().SetZoom(3.f);
		Camera::GetInstance().SetBoundary(0, 0, 6752.f, 3696.f);
		Camera::GetInstance().SetTarget(nullptr);
		Camera::GetInstance().SetPosition(539.f, 3557.f);
		GameObjectManager::GetInstance().AddGameObject<PrologueSkyObj>();
		GameObjectManager::GetInstance().AddGameObject<PrologueCloudObj>();
		InsertLinePlatform({ 0.f, 3568.f }, { 1279.f, 3568.f }, true);
		InsertLinePlatform({ 1279.f, 3568.f }, { 1279.f, 3584.f }, true);
		InsertLinePlatform({ 1279.f, 3584.f }, { 1376.f, 3584.f }, true);
		InsertLinePlatform({ 1376.f, 3584.f }, { 1376.f, 3552.f }, true);
		InsertLinePlatform({ 1376.f, 3552.f }, { 1632.f, 3552.f }, true);
		InsertLinePlatform({ 1632.f, 3552.f }, { 1632.f, 3488.f }, true);
		InsertLinePlatform({ 1632.f, 3488.f }, { 1759.f, 3488.f }, true);
		InsertLinePlatform({ 1759.f, 3488.f }, { 1759.f, 3520.f }, true);
		InsertLinePlatform({ 1759.f, 3520.f }, { 1888.f, 3520.f }, true);
		InsertLinePlatform({ 1888.f, 3520.f }, { 1888.f, 3456.f }, true);
		InsertLinePlatform({ 1888.f, 3456.f }, { 2991.f, 3456.f }, true);
		InsertLinePlatform({ 2991.f, 3456.f }, { 2991.f, 3472.f }, true);
		InsertLinePlatform({ 2991.f, 3472.f }, { 3088.f, 3472.f }, true);
		InsertLinePlatform({ 3088.f, 3472.f }, { 3088.f, 3408.f }, true);
		InsertLinePlatform({ 3088.f, 3408.f }, { 3776.f, 3408.f }, true);
		InsertLinePlatform({ 3776.f, 3408.f }, { 3776.f, 3200.f }, true);
		InsertLinePlatform({ 3776.f, 3200.f }, { 3951.f, 3200.f }, true);
		InsertLinePlatform({ 3951.f, 3200.f }, { 3951.f, 3504.f }, true);
		InsertLinePlatform({ 3951.f, 3504.f }, { 4432.f, 3504.f }, true);
		InsertLinePlatform({ 4432.f, 3504.f }, { 4432.f, 3312.f }, true);
		InsertLinePlatform({ 4432.f, 3311.f }, { 4432.f, 3216.f }, false);
		InsertLinePlatform({ 4432.f, 3215.f }, { 4432.f, 2992.f }, true);
		InsertLinePlatform({ 4432.f, 2991.f }, { 4432.f, 2896.f }, false);
		InsertLinePlatform({ 4432.f, 2895.f }, { 4416.f, 2895.f }, true);
		InsertLinePlatform({ 4416.f, 2895.f }, { 4416.f, 2784.f }, true);
		InsertLinePlatform({ 4416.f, 2784.f }, { 4831.f, 2784.f }, true);

		InsertLinePlatform({ 4831.f, 2784.f }, { 4831.f, 2832.f }, true);
		InsertLinePlatform({ 4831.f, 2832.f }, { 4928.f, 2832.f }, true);
		InsertLinePlatform({ 4928.f, 2832.f }, { 4928.f, 2624.f }, true);
		InsertLinePlatform({ 4928.f, 2624.f }, { 5487.f, 2624.f }, true);
		InsertLinePlatform({ 5487.f, 2624.f }, { 5487.f, 2656.f }, true);
		InsertLinePlatform({ 5487.f, 2656.f }, { 5872.f, 2656.f }, true);
		InsertLinePlatform({ 5872.f, 2656.f }, { 5872.f, 2544.f }, true);
		InsertLinePlatform({ 5872.f, 2544.f }, { 6079.f, 2544.f }, true);
		InsertLinePlatform({ 6079.f, 2544.f }, { 6079.f, 2992.f }, true);
		InsertLinePlatform({ 6079.f, 2992.f }, { 6528.f, 2992.f }, true);
		InsertLinePlatform({ 6528.f, 2992.f }, { 6528.f, 2800.f }, true);
		InsertLinePlatform({ 6528.f, 2799.f }, { 6528.f, 2704.f }, false);
		InsertLinePlatform({ 6528.f, 2703.f }, { 6528.f, 2480.f }, true);
		InsertLinePlatform({ 6528.f, 2479.f }, { 6528.f, 2384.f }, false);
		InsertLinePlatform({ 6528.f, 2383.f }, { 6528.f, 2160.f }, true);
		InsertLinePlatform({ 6528.f, 2159.f }, { 6528.f, 1791.f }, false);
		InsertLinePlatform({ 6528.f, 1791.f }, { 6383.f, 1791.f }, false);
		InsertLinePlatform({ 6382.f, 1791.f }, { 6240.f, 1791.f }, true);
		InsertLinePlatform({ 6239.f, 1791.f }, { 5968.f, 1791.f }, false);
		InsertLinePlatform({ 5967.f, 1791.f }, { 5967.f, 1823.f }, true);
		InsertLinePlatform({ 5967.f, 1823.f }, { 5600.f, 1823.f }, true);
		InsertLinePlatform({ 5600.f, 1823.f }, { 5600.f, 1759.f }, true);
		InsertLinePlatform({ 5600.f, 1759.f }, { 5136.f, 1759.f }, true);
		InsertLinePlatform({ 5136.f, 1759.f }, { 5136.f, 1488.f }, true);
		InsertLinePlatform({ 5136.f, 1488.f }, { 5263.f, 1488.f }, true);
		InsertLinePlatform({ 5264.f, 1488.f }, { 5504.f, 1488.f }, false);
		InsertLinePlatform({ 5504.f, 1488.f }, { 5504.f, 1376.f }, false);
		InsertLinePlatform({ 5504.f, 1376.f }, { 5887.f, 1376.f }, false);
		InsertLinePlatform({ 5888.f, 1376.f }, { 5888.f, 896.f }, true);
		InsertLinePlatform({ 5888.f, 896.f }, { 6000.f, 896.f }, true);
		InsertLinePlatform({ 6000.f, 896.f }, { 6000.f, 303.f }, true);
		InsertLinePlatform({ 6000.f, 303.f }, { 4304.f, 303.f }, true);
		InsertLinePlatform({ 4303.f, 303.f }, { 4064.f, 303.f }, false);

		InsertLinePlatform({ 4032.f, 3439.f }, { 4223.f, 3439.f }, true);
		InsertLinePlatform({ 4223.f, 3439.f }, { 4223.f, 3375.f }, true);
		InsertLinePlatform({ 4223.f, 3375.f }, { 4351.f, 3375.f }, true);
		InsertLinePlatform({ 4351.f, 3375.f }, { 4351.f, 3136.f }, true);
		InsertLinePlatform({ 4351.f, 3136.f }, { 4351.f, 3040.f }, false); // false
		InsertLinePlatform({ 4351.f, 3040.f }, { 4351.f, 2736.f }, true);
		InsertLinePlatform({ 4351.f, 2736.f }, { 4351.f, 2207.f }, false); // false
		InsertLinePlatform({ 4351.f, 2207.f }, { 5520.f, 2207.f }, false); // false
		InsertLinePlatform({ 5520.f, 2207.f }, { 5520.f, 2415.f }, false); // false
		InsertLinePlatform({ 5520.f, 2415.f }, { 5552.f, 2415.f }, true);
		InsertLinePlatform({ 5552.f, 2415.f }, { 5552.f, 2431.f }, true);
		InsertLinePlatform({ 5552.f, 2431.f }, { 5727.f, 2431.f }, true);
		InsertLinePlatform({ 5727.f, 2431.f }, { 5727.f, 2319.f }, true);
		InsertLinePlatform({ 5727.f, 2319.f }, { 6176.f, 2319.f }, false); // false
		InsertLinePlatform({ 6176.f, 2319.f }, { 6176.f, 2815.f }, false); // false
		InsertLinePlatform({ 6176.f, 2815.f }, { 6191.f, 2815.f }, false); // false
		InsertLinePlatform({ 6191.f, 2815.f }, { 6303.f, 2815.f }, true);
		InsertLinePlatform({ 6303.f, 2815.f }, { 6303.f, 2480.f }, true);
		InsertLinePlatform({ 6303.f, 2480.f }, { 6303.f, 2384.f }, false); // false
		InsertLinePlatform({ 6303.f, 2384.f }, { 6303.f, 2048.f }, true);
		InsertLinePlatform({ 6303.f, 2048.f }, { 6000.f, 2048.f }, true);
		InsertLinePlatform({ 6000.f, 2048.f }, { 6000.f, 2080.f }, true);
		InsertLinePlatform({ 6000.f, 2080.f }, { 4959.f, 2080.f }, false); // false
		InsertLinePlatform({ 4959.f, 2080.f }, { 4959.f, 2000.f }, true);
		InsertLinePlatform({ 4959.f, 2000.f }, { 4847.f, 2000.f }, true);
		InsertLinePlatform({ 4847.f, 2000.f }, { 4847.f, 1408.f }, true);
		InsertLinePlatform({ 4847.f, 1408.f }, { 4735.f, 1408.f }, true);
		InsertLinePlatform({ 4735.f, 1408.f }, { 4735.f, 1199.f }, false); // false
		InsertLinePlatform({ 4735.f, 1199.f }, { 5103.f, 1199.f }, true);
		InsertLinePlatform({ 5103.f, 1199.f }, { 5103.f, 1055.f }, true);
		InsertLinePlatform({ 5103.f, 1055.f }, { 5695.f, 1055.f }, true);
		InsertLinePlatform({ 5695.f, 1055.f }, { 5695.f, 624.f }, true);
		InsertLinePlatform({ 5695.f, 624.f }, { 5680.f, 624.f }, true);
		InsertLinePlatform({ 5680.f, 624.f }, { 5215.f, 624.f }, false); // false
		InsertLinePlatform({ 5215.f, 624.f }, { 5215.f, 400.f }, false); // false
		InsertLinePlatform({ 5215.f, 400.f }, { 4480.f, 400.f }, false); // false
		InsertLinePlatform({ 4480.f, 400.f }, { 4480.f, 608.f }, false); // false
		InsertLinePlatform({ 4480.f, 608.f }, { 3232.f, 608.f }, true);
		InsertLinePlatform({ 4032.f, 3439.f }, { 4032.f, 3136.f }, true);
		InsertLinePlatform({ 4032.f, 3136.f }, { 4032.f, 1072.f }, false);

		GameObject* platform = GameObjectManager::GetInstance().AddGameObject<PlatformObject>();
		platform->GetComponent<Platform>()->SetType(RECT_PLATFORM);
		platform->GetComponent<Platform>()->SetGrab(true);
		platform->GetComponent<Platform>()->SetHit(false);
		platform->AddComponent<BoxCollider>();    
		platform->GetTransform()->SetWorldPosition({ 5831.5f, 639.5f});
		platform->GetTransform()->SetLocalScale({ 111.f,95.f });

		GameObject* pt = GameObjectManager::GetInstance().AddGameObject<PotalObj>();
		pt->GetTransform()->SetWorldPosition({ 3926.f,594.f });
		pt->GetTransform()->SetLocalScale({ 100.f,500.f });

	}

	else if(mIndex == 9)
	{
		if (mOwner->GetComponent<Animator>()->IsFinish())
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
			CSoundMgr::Get_Instance()->PlaySound(L"SNBWakeUp.wav", SOUND_PLAYER, gEffectVolume);
			mIndex++;
			mOwner->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"SNB_Awake1"), 0, 5, 80, 80, .08f);
			mOwner->GetComponent<Animator>()->Loop(false);
		}
	}

	else if (mIndex == 10)
	{
		if (mOwner->GetComponent<Animator>()->IsFinish())
		{
			mCurrentTime += TimeManager::GetInstance().GetDeltaTime();

			if (mCurrentTime >= 2.f)
			{
				mCurrentTime = 0;
				mIndex++;
				mOwner->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"SNB_Awake2"), 0, 5, 80, 80, .08f);
				mOwner->GetComponent<Animator>()->Loop(false);
			}
		}
	}

	else if (mIndex == 11 && mKeyDown == true)
	{
		if (mOwner->GetComponent<Animator>()->IsFinish())
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
			CSoundMgr::Get_Instance()->PlaySound(L"ArmEquipping1.wav", SOUND_PLAYER, gEffectVolume);
			mIndex++;
			mKeyDown = false;
			mOwner->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"SNB_StandUp"), 0, 21, 80, 80, .1f);
			mOwner->GetComponent<Animator>()->Loop(false);
		}
	}

	else if (mIndex == 12)
	{
		if (mOwner->GetComponent<Animator>()->IsFinish())
		{
			mIndex++;
			GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front()->GetComponent<SpriteRenderer>()->SetEnable(true);
			GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front()->GetComponent<Animator>()->SetEnable(true);
			mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
			mOwner->GetComponent<Animator>()->SetEnable(false);
		}
	}

	else if(mIndex == 13)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= 1.5f)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			CSoundMgr::Get_Instance()->PlayBGM(L"BGM_PRLG1_ForestDaughter01.wav", gBGMVolume);
			mCurrentTime = 1.5f;
			mIndex++;
		}
		float temp = 3.f + (2.6f - 3.f) * mCurrentTime / 1.5f;
		Camera::GetInstance().SetZoom(temp);
	}

	else if(mIndex == 14)
	{
		mIndex++;
		GameObject* tutoMove = GameObjectManager::GetInstance().AddGameObject<TutoObj>();
		tutoMove->GetTransform()->SetWorldPosition({ 522.f, 3345.f });
		tutoMove->GetTransform()->SetLocalScale({ 100.f,1000.f });
		tutoMove->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"Tuto_Move"), 0, 22, 127, 126, .1f);
		tutoMove->GetComponent<Animator>()->Loop(true);

		GameObject* tutoJump = GameObjectManager::GetInstance().AddGameObject<TutoObj>();
		tutoJump->GetTransform()->SetWorldPosition({ 1234.f, 3345.f });
		tutoJump->GetTransform()->SetLocalScale({ 100.f,1000.f });
		tutoJump->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"Tuto_Jump"), 0, 5, 90, 85, .1f);
		tutoJump->GetComponent<Animator>()->Loop(true);

		GameObject* totuClimb = GameObjectManager::GetInstance().AddGameObject<TutoObj>();
		totuClimb->GetTransform()->SetWorldPosition({ 3612.f, 3200.f });
		totuClimb->GetTransform()->SetLocalScale({ 100.f,1000.f });
		totuClimb->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"Tuto_Climb"), 0, 30, 160, 128, .1f);
		totuClimb->GetComponent<Animator>()->Loop(true);

		GameObject* totuClimbJump = GameObjectManager::GetInstance().AddGameObject<TutoObj>();
		totuClimbJump->GetTransform()->SetWorldPosition({ 4309.f, 3400.f });
		totuClimbJump->GetTransform()->SetLocalScale({ 100.f,1000.f });
		totuClimbJump->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"Tuto_ClimbJump"), 0, 10, 156, 149, .1f);
		totuClimbJump->GetComponent<Animator>()->Loop(true);

		GameObject* totuSwing = GameObjectManager::GetInstance().AddGameObject<TutoObj>();
		totuSwing->GetTransform()->SetWorldPosition({ 5439.f, 2541.f });
		totuSwing->GetTransform()->SetLocalScale({ 100.f,1000.f });
		totuSwing->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"Tuto_Swing"), 0, 64, 160, 160, .1f);
		totuSwing->GetComponent<Animator>()->Loop(true);

		GameObject* totuSwingDash = GameObjectManager::GetInstance().AddGameObject<TutoObj>();
		totuSwingDash->GetTransform()->SetWorldPosition({ 6024.f, 1892.f });
		totuSwingDash->GetTransform()->SetLocalScale({ 100.f,1000.f });
		totuSwingDash->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"Tuto_SwingDash"), 0, 39, 127, 155, .1f);
		totuSwingDash->GetComponent<Animator>()->Loop(true);

		GameObject* totuSwingRush = GameObjectManager::GetInstance().AddGameObject<TutoObj>();
		totuSwingRush->GetTransform()->SetWorldPosition({ 5795.f, 440.f });
		totuSwingRush->GetTransform()->SetLocalScale({ 100.f,800.f });
		totuSwingRush->GetComponent<Animator>()->MotionChange(ImageManager::GetInstance().FindImage(L"Tuto_SwingRush"), 0, 20, 127, 167, .1f);
		totuSwingRush->GetComponent<Animator>()->Loop(true);


		mOwner->GetTransform()->SetWorldPosition({ 2208.f,3446.f });
		mOwner->GetTransform()->SetLocalScale({ 50.f, 500.f });
		mOwner->AddComponent<BoxCollider>();
	}

	else if(mIndex == 16)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= 1.5f)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			CSoundMgr::Get_Instance()->PlayBGM(L"BGM_PRLG1_ForestDaughter01.wav", gBGMVolume);
			mCurrentTime = 1.5f;
			mIndex++;
		}
		float temp = 2.6f + (1.4f - 2.6f) * mCurrentTime / 1.5f;
		Camera::GetInstance().SetZoom(temp);
	}

	if (KeyManager::Get_Instance()->Key_Down('E'))
	{
		mKeyDown = true;
	}
}

void PRLG::InsertLinePlatform(const Vector2& start, const Vector2& end, bool grab)
{
	GameObject* platform = GameObjectManager::GetInstance().AddGameObject<PlatformObject>();
	platform->GetComponent<Platform>()->SetType(LINE_PLATFORM);
	platform->GetComponent<Platform>()->SetGrab(grab);
	platform->GetComponent<Platform>()->SetHit(false);
	platform->AddComponent<EdgeCollider>(start, end);
}

void PRLG::OnCollisionEnter(Collision other)
{
	if (other.GetGameObject()->CompareTag(PLAYER))
	{
		if (mIndex == 15)
		{
			mIndex++;
			mCurrentTime = 0;
		}
	}
}
