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
	explicit Collider(GameObject* owner, ColliderType type) : Behaviour(owner), mType(type), mOffset({0,0}),
	                                                          mIsTrigger(false)
	{
	}

	~Collider() override = default;

	virtual void Init() = 0;
	virtual bool CheckCollision(Collider* other, Vector2& contactPoint) = 0;
	virtual void UpdateRect() = 0;
	virtual D2D1_RECT_F* GetRect() = 0;

	ColliderType GetType() const { return mType; }

	bool IsTrigger() const { return mIsTrigger; }
	void SetTrigger(const bool trigger) { mIsTrigger = trigger; }
	void SetOffset(const Vector2& offset) { mOffset = offset; }

	void Destroy() final;

	virtual void Debug(ID2D1DeviceContext* render) = 0;

protected:
	ColliderType mType;
	Vector2		mOffset;
	bool mIsTrigger;
};

