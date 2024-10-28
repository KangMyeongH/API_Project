#include "pch.h"
#include "FireBirdManager.h"

#include "SoundMgr.h"

void FireBirdManager::Awake()
{
	mUpdateType = UPDATE;
}

void FireBirdManager::Update()
{
	if (!mIsBgmLoop && !CSoundMgr::Get_Instance()->IsPlaying(SOUND_INTRO_BGM))
	{
		CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Chap4_MidBoss_Loop.wav", gBGMVolume);
		mIsBgmLoop = true;
	}
}
