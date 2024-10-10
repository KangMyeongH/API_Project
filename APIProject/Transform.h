#pragma once
#include <vector>

#include "Component.h"
class GameObject;

class Transform final : public Component
{
public:
	Transform(GameObject* owner)
		: Component(owner), mLocalPosition{ 0,0 }, mLocalRotation(0), mLocalScale{ 1.f, 1.f }, mParent(nullptr),
		mWorldPosition{ 0.f,0.f }, mWorldRotation(0), mWorldScale(1.f, 1.f), mIsDirty(false) {}

	// Local Position getter and setter
	Vector2 GetLocalPosition() const { return mLocalPosition; }
	void SetLocalPosition(const Vector2& position)
	{
		mLocalPosition = position;
		MarkDirty();
	}

	// World Position getter
	Vector2 GetWorldPosition()
	{
		if (mIsDirty)
		{
			UpdateWorldTransform();
		}
		return mWorldPosition;
	}

	void SetWorldPosition(const Vector2& position)
	{
		if (mParent)
		{
			mLocalPosition = position - mParent->GetWorldPosition();
		}
		else
		{
			mLocalPosition = position;
		}
		MarkDirty();
	}

	// Local Rotation getter and setter
	float GetLocalRotation() const { return mLocalRotation; }
	void SetLocalRotation(float rotation)
	{
		mLocalRotation = rotation;
		MarkDirty();
	}

	// World Rotation getter
	float GetWorldRotation()
	{
		if (mIsDirty)
		{
			UpdateWorldTransform();
		}
		return mWorldRotation;
	}

	// Local Scale getter and setter
	Vector2 GetLocalScale() const { return mLocalScale; }
	void SetLocalScale(const Vector2& scale)
	{
		mLocalScale = scale;
		MarkDirty();
	}

	// World Scale getter
	Vector2 GetWorldScale()
	{
		if (mIsDirty)
		{
			UpdateWorldTransform();
		}
		return mWorldScale;
	}

	// Local position manipulation
	void Translate(const Vector2& delta)
	{
		mLocalPosition += delta;
		MarkDirty();
	}

	// Transform hierarchy management
	void SetParent(Transform* parent)
	{
		if (mParent != nullptr)
		{
			mParent->RemoveChild(this);
		}
		mParent = parent;
		if (mParent != nullptr)
		{
			mParent->AddChild(this);
		}
		MarkDirty();
	}

	Transform* GetParent() const { return mParent; }
	const std::vector<Transform*>& GetChildren() const { return mChildren; }

private:
	void AddChild(Transform* child) { mChildren.push_back(child); }
	void RemoveChild(Transform* child)
	{
		mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), child), mChildren.end());
	}


	void Update();

private:

	Vector2						mLocalPosition;
	float						mLocalRotation;
	Vector2						mLocalScale;
	Transform* 					mParent;
	std::vector<Transform*> 	mChildren;
	Vector2 					mWorldPosition;
	float 						mWorldRotation;
	Vector2 					mWorldScale;
	bool 						mIsDirty;
};