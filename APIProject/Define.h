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

extern HWND gHwnd;

using GameObjectList = std::list<GameObject*>;