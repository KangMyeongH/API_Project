#pragma once
#include <list>

#include "framework.h"

class GameObject;

enum { WIN_WIDTH = 800, WIN_HEIGHT = 600 };
enum Tag
{
	UNTAGGED,
	PLAYER,
	MONSTER,
	ITEM,
	END_TAG
};

enum CollisionDirection
{
	NONE = 0,
	LEFT = 1 << 0,       // 0001
	RIGHT = 1 << 1,    // 0010
	TOP = 1 << 2,       // 0100
	BOTTOM = 1 << 3    // 1000
};

extern HWND gHwnd;

using GameObjectList = std::list<GameObject*>;