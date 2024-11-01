#include "pch.h"
#include "TitleScene.h"

#include "BlackBGObj.h"
#include "BubbleObj.h"
#include "GameObjectManager.h"
#include "JusinLogoObj.h"
#include "MainTitleBGObj.h"
#include "MouseObj.h"
#include "SoundMgr.h"

void TitleScene::Init()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Event_MainTheme.wav", gBGMVolume);
	GameObjectManager::GetInstance().AddGameObject<MouseObj>();
	GameObjectManager::GetInstance().AddGameObject<BlackBGObj>();
	GameObjectManager::GetInstance().AddGameObject<JusinLogoObj>();
	GameObjectManager::GetInstance().AddGameObject<MainTitleBGObj>();

}