#include "pch.h"
#include "Mouse.h"

#include "Transform.h"

void Mouse::Awake()
{
	mUpdateType = UPDATE;
}

void Mouse::Update()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);

	GetTransform()->SetWorldPosition({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) });
}
