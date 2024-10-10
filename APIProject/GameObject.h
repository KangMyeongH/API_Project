#pragma once
#include <typeindex>
#include <unordered_map>

#include "Transform.h"

class GameObject
{
public:
	GameObject() : mTransform(this), mActiveSelf(true), mTag(UNTAGGED)
	{
	}

	virtual ~GameObject()
	{
		// 각각의 컴포넌트 매니저와 monoBehavior매니저의 객체들을 삭제해주는 작업을 해야함
	}

	Transform* GetTransform() { return &mTransform; }

	// Component management
	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		T* component = new T(this, std::forward<Args>(args)...);
		mComponents.push_back(component);
		mComponentMap[typeid(T)].push_back(component);
		return component;
	}

	template <typename T>
	T* GetComponent() const
	{
		auto it = mComponentMap.find(typeid(T));
		if (it != mComponentMap.end() && !it->second.empty())
		{
			return static_cast<T*>(it->second.front());
		}
		return nullptr;
	}

	bool CompareTag(const Tag tag) const { return mTag == tag; }
	void SetTag(const Tag tag) { mTag = tag; }
	Tag GetTag() const { return mTag; }

	void SetActive(bool active)
	{
		if (mActiveSelf != active)
		{
			mActiveSelf = active;
			MarkDirty();
		}
	}

	bool IsActiveSelf() const { return mActiveSelf; }
	bool IsActiveInHierarchy() const
	{
		if (mTransform.GetParent() && !mTransform.GetParent()->GetGameObject()->IsActiveInHierarchy())
		{
			return false;
		}
		return mActiveSelf;
	}

	virtual void Init() = 0;

private:
	void MarkDirty() const
	{
		for (Transform* child : mTransform.GetChildren())
		{
			child->GetGameObject()->MarkDirty();
		}
	}

private:
	Transform mTransform;
	std::vector<Component*> mComponents;
	std::unordered_map<std::type_index, std::vector<Component*>> mComponentMap;
	bool mActiveSelf;
	Tag mTag;
};
