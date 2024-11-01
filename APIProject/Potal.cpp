#include "pch.h"
#include "Potal.h"

#include "FireBirdScene.h"
#include "GameObject.h"
#include "PrologueScene.h"
#include "SceneManager.h"

void Potal::OnCollisionEnter(Collision other)
{
	if (other.GetGameObject()->CompareTag(PLAYER))
	{
		SceneManager::GetInstance().ChangeScene(new FireBirdScene);
	}
}
