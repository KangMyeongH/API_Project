#include "pch.h"
#include "PrologueScene.h"

#include "BlackBGObj.h"
#include "EdgeCollider.h"
#include "GameObjectManager.h"
#include "GrabObject.h"
#include "Platform.h"
#include "PlatformObject.h"
#include "PlayerObject.h"
#include "PRLGMgr.h"
#include "PrologueMapObj.h"
#include "PrologueSkyObj.h"

void PrologueScene::Init()
{
	GameObjectManager::GetInstance().AddGameObject<BlackBGObj>();
	GameObjectManager::GetInstance().AddGameObject<PRLGMgr>();

	/*
	GameObjectManager::GetInstance().AddGameObject<PrologueMapObj>();
	GameObjectManager::GetInstance().AddGameObject<PlayerObject>();
	GameObjectManager::GetInstance().AddGameObject<GrabObject>();
	Camera::GetInstance().SetBoundary(0, 0, 6752.f, 3696.f);
	GameObjectManager::GetInstance().AddGameObject<PrologueSkyObj>();

	InsertLinePlatform({ 0.f, 3568.f }, { 1279.f, 3568.f },true);
	InsertLinePlatform({ 1279.f, 3568.f }, { 1279.f, 3584.f },true);
	InsertLinePlatform({ 1279.f, 3584.f }, { 1376.f, 3584.f },true);
	InsertLinePlatform({ 1376.f, 3584.f }, { 1376.f, 3552.f },true);
	InsertLinePlatform({ 1376.f, 3552.f }, { 1632.f, 3552.f },true);
	InsertLinePlatform({ 1632.f, 3552.f }, { 1632.f, 3488.f },true);
	InsertLinePlatform({ 1632.f, 3488.f }, { 1759.f, 3488.f },true);
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
	*/
}

void PrologueScene::InsertLinePlatform(const Vector2& start, const Vector2& end, bool grab)
{
	GameObject* platform = GameObjectManager::GetInstance().AddGameObject<PlatformObject>();
	platform->GetComponent<Platform>()->SetType(LINE_PLATFORM);
	platform->GetComponent<Platform>()->SetGrab(grab);
	platform->GetComponent<Platform>()->SetHit(false);
	platform->AddComponent<EdgeCollider>(start, end);
}