#pragma once
#include "Behaviour.h"

enum class ColliderType
{
	Box,
	Edge
};

class Collider : public Behaviour
{
public:
	explicit Collider(GameObject* owner, ColliderType type) : Behaviour(owner), mType(type), mIsTrigger(false) {}

	~Collider() override = default;

	virtual void Init() = 0;
	virtual bool CheckCollision(Collider* other, POINT& contactPoint) = 0;
	virtual void UpdateRect() = 0;
	virtual RECT* GetRect() = 0;

	ColliderType GetType() const { return mType; }

	bool IsTrigger() const { return mIsTrigger; }
	void SetTrigger(const bool trigger) { mIsTrigger = trigger; }

	void Destroy() final;

protected:
	ColliderType mType;
	bool mIsTrigger;
};

