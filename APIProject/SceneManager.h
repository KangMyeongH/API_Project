#pragma once

class Scene;
class SceneManager
{
private:
	SceneManager() = default;
	~SceneManager();
public:
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

public:
	static SceneManager& GetInstance() { static SceneManager sMgr; return sMgr; }

	void Init(Scene* startScene);

	void ChangeScene(Scene* scene);

	void RegisterScene();

	void Release();
private:
	Scene* mPendingScene;
	Scene* mCurrentScene;
};

