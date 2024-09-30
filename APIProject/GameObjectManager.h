#pragma once
class GameObjectManager
{
private:
	GameObjectManager() = default;
	~GameObjectManager();
public:
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager(GameObjectManager&&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;
	GameObjectManager& operator=(GameObjectManager&&) = delete;

	static GameObjectManager& GetInstance() { static GameObjectManager sManager; return sManager; }

	void 		Init(const GameObjectList* objectList);
	void 		Start();
	void 		Update();
	void 		LateUpdate();
	void 		Render(HDC& hdc);
	void 		OnDestroy();
	void 		Release();

	void		AddGameObject(GameObject* object);
	void		AddDestroy(GameObject* object);

	GameObjectList& GetGameObjectsByTag(Tag tag);

private:
	GameObjectList mActiveObjects;
	GameObjectList mPendingObjects;
	GameObjectList mDestroyObjects;
	GameObjectList mGameObjects[END_TAG];
};