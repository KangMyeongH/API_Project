#pragma once
#include <vector>
#include "Component.h"

class GameObject;

class Transform final : public Component
{
public:
	explicit Transform(GameObject* owner)
		: Component(owner), mLocalPosition{ 0,0 }, mLocalRotation(0), mLocalScale{ 1.f, 1.f }, mWorldPosition{ 0.f,0.f },
		mWorldRotation(0), mWorldScale(1.f, 1.f), mParent(nullptr) {}

	// Local Position getter and setter
	Vector2 GetLocalPosition() const { return mLocalPosition; }
	void SetLocalPosition(const Vector2& position)
	{
		mLocalPosition = position;
		UpdateWorldPosition();
		UpdateChildrenWorldPosition();
	}

	// World Position getter
	Vector2 GetWorldPosition() const { return mWorldPosition; }
	void SetWorldPosition(const Vector2& position)
	{
		if (mParent)
		{
			SetLocalPosition(position - mParent->GetWorldPosition());
		}

		else
		{
			SetLocalPosition(position);
		}
	}

	// Local Rotation getter and setter
	float GetLocalRotation() const { return mLocalRotation; }
	void SetLocalRotation(const float rotation)
	{
		mLocalRotation = rotation;
		UpdateWorldRotation();
		UpdateChildrenWorldRotation();
	}

	// World Rotation getter
	float GetWorldRotation() const { return mWorldRotation; }

	// Local Scale getter and setter
	Vector2 GetLocalScale() const { return mLocalScale; }
	void SetLocalScale(const Vector2& scale)
	{
		mLocalScale = scale;
		UpdateWorldScale();
		UpdateChildrenWorldScale();
	}

	// World Scale getter
	Vector2 GetWorldScale() const { return mWorldScale; }

	// Local position manipulation
	void Translate(const Vector2& delta)
	{
		if (delta.x != 0.f || delta.y != 0.f)
		{
			mLocalPosition += delta;
			UpdateWorldPosition();
			UpdateChildrenWorldPosition();
		}
	}

	// Transform hierarchy management
	void SetParent(Transform* parent)
	{
		if (mParent != parent)
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

			else
			{
				// Clear parent
				UpdateWorldTransform();
				UpdateChildrenTransforms();
			}
		}
	}

	Transform* GetParent() const { return mParent; }
	const std::vector<Transform*>& GetChildren() const { return mChildren; }

	void Destroy() override {}

private:
	void AddChild(Transform* child) { mChildren.push_back(child); }
	void RemoveChild(Transform* child)
	{
		mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), child), mChildren.end());
	}

	void UpdateWorldPosition()
	{
		if (mParent)
		{
			mWorldPosition = mParent->GetLocalPosition() + mLocalPosition;
		}

		else
		{
			mWorldPosition = mLocalPosition;
		}
	}

	void UpdateWorldRotation()
	{
		if (mParent)
		{
			mWorldRotation = mParent->GetWorldRotation() + mLocalRotation;
		}
		else
		{
			mWorldRotation = mLocalRotation;
		}
	}

	void UpdateWorldScale()
	{
		if (mParent)
		{
			mWorldScale = Vector2(mLocalScale.x * mParent->GetWorldScale().x, mLocalScale.y * mParent->GetWorldScale().y);
		}

		else
		{
			mWorldScale = mLocalScale;
		}
	}

	void UpdateChildrenWorldPosition()
	{
		for (Transform* child : mChildren)
		{
			child->UpdateWorldPosition();
			child->UpdateChildrenWorldPosition();
		}
	}

	void UpdateChildrenWorldRotation()
	{
		for (Transform* child : mChildren)
		{
			child->UpdateWorldRotation();
			child->UpdateChildrenWorldRotation();
		}
	}

	void UpdateChildrenWorldScale()
	{
		for (Transform* child : mChildren)
		{
			child->UpdateWorldScale();
			child->UpdateChildrenWorldScale();
		}
	}

	void UpdateWorldTransform()
	{
		UpdateWorldPosition();
		UpdateWorldRotation();
		UpdateWorldScale();
	}

	void UpdateChildrenTransforms()
	{
		UpdateChildrenWorldPosition();
		UpdateChildrenWorldRotation();
		UpdateChildrenWorldScale();
	}

private:
	Vector2						mLocalPosition;
	float						mLocalRotation;
	Vector2						mLocalScale;

	Vector2 					mWorldPosition;
	float 						mWorldRotation;
	Vector2 					mWorldScale;

	Transform* 					mParent;
	std::vector<Transform*> 	mChildren;
};