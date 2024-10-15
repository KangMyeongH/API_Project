#include "pch.h"
#include "PlayerObject.h"

#include "Animator.h"
#include "BitMapManager.h"
#include "BoxCollider.h"
#include "Player.h"
#include "SpriteRenderer.h"

void PlayerObject::Init()
{
	mTransform.SetWorldPosition({ 300, 300 });
	AddComponent<Rigidbody>(0, true, 0, 0, DYNAMIC);
	GetComponent<Rigidbody>()->SetUseGravity(false);
	AddComponent<BoxCollider>();
	AddComponent<SpriteRenderer>();
	AddComponent<Animator>();
	AddComponent<Player>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	GetComponent<Animator>()->Loop(true);
}
