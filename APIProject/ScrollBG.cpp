#include "pch.h"
#include "ScrollBG.h"

#include "GameObject.h"
#include "GameObjectManager.h"

void ScrollBG::Init(Transform* bg1, Transform* bg2, float speed)
{
	mLinkBG[0] = bg1;
	mLinkBG[1] = bg2;
	mSpeed = speed;
}

void ScrollBG::Awake()
{
	mUpdateType = LATE_UPDATE;
}

void ScrollBG::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();
	mWidth = mLinkBG[0]->GetGameObject()->GetComponent<SpriteRenderer>()->GetWidth();
	mLinkBG[1]->SetWorldPosition({ mLinkBG[0]->GetWorldPosition().x + mWidth, mLinkBG[0]->GetWorldPosition().y });
}

void ScrollBG::LateUpdate()
{
	D2D1_RECT_F boundary = Camera::GetInstance().GetBoundary();
	for (auto& transform : mLinkBG)
	{
		transform->Translate({ mSpeed,0 });
		transform->SetWorldPosition({ transform->GetWorldPosition().x, mPlayer->GetTransform()->GetWorldPosition().y * 0.3f + 800.f });
	}

	for (int i = 0; i < 2; ++i)
	{
		float test = mLinkBG[i]->GetWorldPosition().x + mWidth * 0.5f;
		if (mLinkBG[i]->GetWorldPosition().x + mWidth * 0.5f <= 0)
		{
			int index = (i == 0) ? 1 : 0;

			mLinkBG[i]->SetWorldPosition({ (mLinkBG[index]->GetWorldPosition().x + mWidth), mLinkBG[i]->GetWorldPosition().y });
		}
	}

	for (auto& transform : mLinkBG)
	{
		transform->GetGameObject()->GetComponent<SpriteRenderer>()->SetFrame(0);
	}
}