#pragma once
#include <vector>
class SpriteRenderer;

class RenderManager
{
private:
	RenderManager() = default;
	~RenderManager();
public:
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	RenderManager& operator=(RenderManager&&) = delete;

public:
	static RenderManager& GetInstance() { static RenderManager sMgr; return sMgr; }

	void RegisterForUpdate();

	void ClearDestroyColliderQueue();

	void AddSprite(SpriteRenderer* sprite);

	void RemoveSprite(SpriteRenderer* sprite);

	void Rendering(HDC hdc) const;

private:
	std::vector<SpriteRenderer*> 	mSprites;
	std::list<SpriteRenderer*>		mPendingSpriteQueue;
	std::list<SpriteRenderer*>		mDestroySpriteQueue;
};
