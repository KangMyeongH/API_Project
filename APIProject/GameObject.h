#pragma once
#include <typeindex>
#include <unordered_map>

#include "MonoBehaviour.h"
#include "MonoBehaviourManager.h"
#include "Transform.h"

class MonoBehaviourManager;

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
		if (dynamic_cast<MonoBehaviour*>(component))
			MonoBehaviourManager::GetInstance().AddMonoBehaviour(dynamic_cast<MonoBehaviour*>(component));
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

	template <typename T>
	void RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		auto mapIter = mComponentMap.find(typeid(T));
		Component* component = GetComponent<T>();
		mComponentMap.erase(mapIter);
		mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), component), mComponents.end());

		if (dynamic_cast<MonoBehaviour*>(component))
			MonoBehaviourManager::GetInstance().RemoveBehaviour(dynamic_cast<MonoBehaviour*>(component));
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

	void Destroy();

	virtual void Init() = 0;


private:
	void MarkDirty() const
	{
		for (Transform* child : mTransform.GetChildren())
		{
			child->GetGameObject()->MarkDirty();
		}
	}

	void Release()
	{
		for (auto iter = mComponents.begin(); iter != mComponents.end();)
		{
			(*iter)->Destroy();
		}
	}

private:
	Transform mTransform;
	std::vector<Component*> mComponents;
	std::unordered_map<std::type_index, std::vector<Component*>> mComponentMap;
	bool mActiveSelf;
	Tag mTag;
};
