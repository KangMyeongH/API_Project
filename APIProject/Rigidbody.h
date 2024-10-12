#pragma once
#include "Behaviour.h"

enum BodyType
{
	DYNAMIC = 1 << 0,		// 001
	KINEMATIC = 1 << 1,		// 010
	STATIC = 1 << 2			// 100
};

class Rigidbody final : public Behaviour
{
public:
	Rigidbody(GameObject* owner);
	Rigidbody(GameObject* owner, float mass, bool useGravity, float drag, float angularDrag, BodyType type);
	~Rigidbody() override = default;
	Rigidbody(const Rigidbody&) = delete;
	Rigidbody(Rigidbody&&) = delete;
	Rigidbody& operator=(const Rigidbody&) = delete;
	Rigidbody& operator=(Rigidbody&&) = delete;

	void 		SetVelocity(const Vector2& velocity) { mVelocity = velocity; }
	Vector2 	GetVelocity() const { return mVelocity; }

	void		SetPrevPosition(const Vector2& position) { mPrevPosition = position; }
	Vector2		GetPrevPosition() const { return mPrevPosition; }

	void 		SetMass(const float mass) { mMass = mass; }
	float 		GetMass() const { return mMass; }

	void 		SetUseGravity(const bool useGravity) { mUseGravity = useGravity; }
	bool 		GetUseGravity() const { return mUseGravity; }

	void 		SetDrag(const float drag) { mDrag = drag; }
	float 		GetDrag() const { return mDrag; }

	void 		SetAngularDrag(const float angularDrag) { mAngularDrag = angularDrag; }
	float 		GetAngularDrag() const { return mAngularDrag; }

	void		AddForce(const Vector2& force) { mVelocity += force / mMass; }

	void		MovePosition(const Vector2& position);
	void		MoveRotation(float rotation) const;

	void 		Update(float deltaTime);
	void 		Destroy() override;

private:
	Vector2 	mVelocity;
	Vector2		mPrevPosition;
	float 		mMass;				// 무게 (AddForce에 관여)
	bool 		mUseGravity;
	float 		mDrag;				// 공기 저항 값 (크면 클수록 속도를 강하게 줄임)
	float		mAngularDrag;		// 공기 각저항 값
	BodyType	mBodyType;
};