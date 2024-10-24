#pragma once
#include "Behaviour.h"
class Renderer : public Behaviour
{
public:
	explicit Renderer(GameObject* owner, int layer)
		: Behaviour(owner), mLayer(layer)
	{
	}

	virtual void Render(ID2D1HwndRenderTarget* render) = 0;
	int		GetLayer() const { return mLayer; }
	void	Destroy() override;

protected:
	int mLayer;
};

