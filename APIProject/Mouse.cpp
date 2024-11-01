#include "pch.h"
#include "Mouse.h"

#include "GameObject.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Transform.h"

void Mouse::Awake()
{
	mUpdateType = UPDATE;
}

void Mouse::Update()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);


	GetTransform()->SetWorldPosition({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) });
	mOwner->GetComponent<SpriteRenderer>()->SetFrame(0);

	if (KeyManager::Get_Instance()->Key_Down('G'))
	{
		SceneManager::GetInstance().ChangeScene(new TitleScene);
	}
}
