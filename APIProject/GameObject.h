#pragma once
#include <typeindex>
#include <unordered_map>

#include "AnimatorManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "MonoBehaviour.h"
#include "MonoBehaviourManager.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
#include "Animator.h"

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
		{
			MonoBehaviourManager::GetInstance().AddMonoBehaviour(dynamic_cast<MonoBehaviour*>(component));
			return component;
		}

		if (dynamic_cast<Rigidbody*>(component))
		{
			PhysicsManager::GetInstance().AddRigidbody(dynamic_cast<Rigidbody*>(component));
			return component;
		}

		if (dynamic_cast<Collider*>(component))
		{
			CollisionManager::GetInstance().AddCollider(dynamic_cast<Collider*>(component));
			return component;
		}

		if (dynamic_cast<Renderer*>(component))
		{
			RenderManager::GetInstance().AddRenderer(dynamic_cast<Renderer*>(component));
			return component;
		}

		if (dynamic_cast<Animator*>(component))
		{
			AnimatorManager::GetInstance().AddAnimator(dynamic_cast<Animator*>(component));
			return component;
		}

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
	std::vector<T*>* GetComponents() const
	{
		auto it = mComponentMap.find(typeid(T));
		if (it != mComponentMap.end() && !it->second.empty())
		{
			return &it->second;
		}
		return nullptr;
	}

	void RemoveComponent(Component* component)
	{
		mComponents.erase(remove(mComponents.begin(), mComponents.end(), component), mComponents.end());

		for (auto it = mComponentMap.begin(); it != mComponentMap.end();)
		{
			if (!it->second.empty() && it->second.front() == component)
			{
				mComponentMap.erase(it);
				return;
			}

			++it;
		}
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
	void OnCollisionEnter(Collision other);
	void OnCollisionStay(Collision other);
	void OnCollisionExit(Collision other);


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

protected:
	Transform mTransform;
	std::vector<Component*> mComponents;
	std::unordered_map<std::type_index, std::vector<Component*>> mComponentMap;
	bool mActiveSelf;
	Tag mTag;
};
