#pragma once
#include <map>
#include <vector>
class Renderer;
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

	void AddRenderer(Renderer* sprite);

	void RemoveRenderer(Renderer* sprite);

	void Rendering(ID2D1DeviceContext* render) const;

	void Release();

private:
	std::vector<Renderer*> 					mRenders;
	std::multimap<int, Renderer*>			mLayerMultiMap;
	std::list<Renderer*>					mPendingRenderQueue;
	std::list<Renderer*>					mDestroyRenderQueue;
};

