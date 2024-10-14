#include "pch.h"
#include "Rigidbody.h"
#include "GameObject.h"

Rigidbody::Rigidbody(GameObject* owner) : Behaviour(owner), mVelocity(0.f, 0.f), mMass(1.f),
mUseGravity(true), mDrag(0.f), mAngularDrag(0.05f), mBodyType(DYNAMIC)
{
	mPrevPosition = mOwner->GetTransform()->GetWorldPosition();
}

Rigidbody::Rigidbody(GameObject* owner, float mass, bool useGravity, float drag, float angularDrag, BodyType type)
	: Behaviour(owner), mMass(mass), mUseGravity(useGravity), mDrag(drag), mAngularDrag(angularDrag), mBodyType(type)
{
	mPrevPosition = mOwner->GetTransform()->GetWorldPosition();
}

void Rigidbody::MovePosition(const Vector2& position)
{
	mPrevPosition = mOwner->GetTransform()->GetWorldPosition();
	mOwner->GetTransform()->Translate(position);
}

void Rigidbody::MoveRotation(const float rotation) const
{
	mOwner->GetTransform()->SetLocalRotation(rotation);
}

void Rigidbody::Update(const float deltaTime)
{
	if (mBodyType & KINEMATIC) return;

	// Apply Gravity
	if (mUseGravity)
	{
		mVelocity.y -= 9.81f * deltaTime;
	}

	// Apply Drag
	mVelocity.x *= 1.0f / (1.0f + mDrag * deltaTime);
	mVelocity.y *= 1.0f / (1.0f + mDrag * deltaTime);

	Transform* transform = mOwner->GetTransform();
	if (transform)
	{
		transform->Translate(mVelocity * deltaTime);
	}
}

void Rigidbody::Destroy()
{
	// Rigidbody Manager의 컨테이너에 담긴 Rigidbody제거
	PhysicsManager::GetInstance().RemoveRigidbody(this);
	mOwner->RemoveComponent(this);
}
