#include "pch.h"
#include "AnimatorManager.h"

#include "Animator.h"
#include "GameObjectManager.h"

AnimatorManager::~AnimatorManager()
{
	for (auto& animator : mAnimators)
	{
		delete animator;
	}

	for (auto& animator : mPendingAnimatorQueue)
	{
		delete animator;
	}
}

void AnimatorManager::RegisterForUpdate()
{
	for (auto it = mPendingAnimatorQueue.begin(); it != mPendingAnimatorQueue.end();)
	{
		Animator* animator = *it;

		if (animator->IsEnabled())
		{
			mAnimators.push_back(animator);

			it = mPendingAnimatorQueue.erase(it);
		}

		else ++it;
	}
}

void AnimatorManager::ClearDestroyAnimatorQueue()
{
	for (auto& animator : mDestroyAnimatorQueue)
	{
		GameObjectList* objList = GameObjectManager::GetInstance().GetGameObjectList();
		for (int i = 0; i < END_TAG; ++i)
		{
			for (auto& go : objList[i])
			{
				if (go == animator->GetGameObject())
				{
					animator->GetGameObject()->RemoveComponent(animator);
					i = END_TAG;
					break;
				}
			}
		}

		delete animator;
		mAnimators.erase(std::remove(mAnimators.begin(), mAnimators.end(), animator), mAnimators.end());
	}

	mDestroyAnimatorQueue.clear();
}

void AnimatorManager::AddAnimator(Animator* animator)
{
	mPendingAnimatorQueue.push_back(animator);
}

void AnimatorManager::RemoveAnimator(Animator* animator)
{
	for (auto& ani : mDestroyAnimatorQueue)
	{
		if (ani == animator)
		{
			return;
		}
	}
	mDestroyAnimatorQueue.push_back(animator);
}

void AnimatorManager::UpdateAnimator()
{
	for (auto& animator : mAnimators)
	{
		if (animator->IsEnabled())
		{
			animator->MoveFrame();
		}
	}
}

void AnimatorManager::Release()
{
	for (auto& animator : mAnimators)
	{
		delete animator;
	}

	for (auto& animator : mPendingAnimatorQueue)
	{
		delete animator;
	}

	mAnimators.clear();
	mPendingAnimatorQueue.clear();
}
