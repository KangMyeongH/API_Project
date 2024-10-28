#pragma once
#include "MonoBehaviour.h"
class Enemy : public MonoBehaviour
{
public:
	Enemy(GameObject* owner, EnemyType type) : MonoBehaviour(owner), mType(type) {}
	~Enemy() override = default;

	EnemyType GetType() const { return mType; }

protected:
	EnemyType	mType;
};

