#include "pch.h"

#include "GameObject.h"
#include "Monobehaviour.h"
#include "MonoBehaviourManager.h"

void MonoBehaviour::Destroy()
{
	MonoBehaviourManager::GetInstance().RemoveBehaviour(this);
	mOwner->RemoveComponent(this);
}
