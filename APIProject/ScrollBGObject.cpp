#include "pch.h"
#include "ScrollBGObject.h"

#include "GameObjectManager.h"
#include "ScrollBG.h"

void ScrollBGObject::Init()
{
	AddComponent<ScrollBG>();
}
