#include "pch.h"
#include "EnemyObject.h"

#include "BoxCollider.h"

void EnemyObject::Init()
{
	mTransform.SetWorldPosition({ 400, 300 });
	mTransform.SetLocalScale({ 24,42 });
	mTag = ENEMY;
	AddComponent<Rigidbody>(0, true, 0, 0, DYNAMIC);
	GetComponent<Rigidbody>()->SetUseGravity(false);
	AddComponent<BoxCollider>();
}
