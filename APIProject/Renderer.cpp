#include "pch.h"
#include "Renderer.h"

#include "RenderManager.h"

void Renderer::Destroy()
{
	RenderManager::GetInstance().RemoveRenderer(this);
}
