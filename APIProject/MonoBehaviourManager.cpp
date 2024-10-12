#include "pch.h"
#include "MonoBehaviourManager.h"

MonoBehaviourManager::~MonoBehaviourManager()
{
	for (auto& mb : mMonoBehaviours)
	{
		delete mb;
	}

	for (auto& mb :mPendingQueue)
	{
		delete mb;
	}

	for (auto& mb : mDestroyQueue)
	{
		delete mb;
	}
}