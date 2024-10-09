#pragma once
#include "Define.h"
#include "GameObjectManager.h"
#include "Transform.h"

class Collider;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject() 						= default;
	GameObject(const GameObject&) 				= delete;
	GameObject(GameObject&&) 					= delete;
	GameObject& operator=(const GameObject&) 	= delete;
	GameObject& operator=(GameObject&&) 		= delete;

	// ��ü�� ������ �� ȣ��
	virtual void 		Init() 								= 0;
	// ��ü�� ������ �� ù �����ӿ� �� �ѹ� ȣ��
	virtual void 		Start()								= 0;
	virtual void		FixedUpdate() 						= 0;
	virtual void 		Update() 							= 0;
	virtual void 		LateUpdate() 						= 0;
	virtual void 		Render(HDC& hdc) 					= 0;
	virtual void 		OnCollisionEnter(Collider* other) 	= 0;

	bool 					CompareTag(Tag tagName) const;
	static void 			Destroy(GameObject* object);
	static GameObjectList& 	FindGameObjectsWithTag(Tag tag);

	template<typename T>
	static std::enable_if_t<std::is_base_of<GameObject, T>::value, GameObject*> AddGameObject()
	{
		GameObject* newObject = new T();
		GameObjectManager::GetInstance().AddGameObject(newObject);
		newObject->Init();
		return newObject;
	}

	Transform& 		GetTransform();
	Tag				GetTag() const;

protected:
	Collider* 		mCollider;
	Transform 		mTransform;
	Tag 			mTag;
};