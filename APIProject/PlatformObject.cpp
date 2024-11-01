#include "pch.h"
#include "PlatformObject.h"

#include "Platform.h"

void PlatformObject::Init()
{
	mTag = PLATFORM;
	AddComponent<Platform>();
}
