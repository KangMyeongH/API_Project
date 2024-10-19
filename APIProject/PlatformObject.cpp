#include "pch.h"
#include "PlatformObject.h"

#include "BoxCollider.h"
#include "Platform.h"

void PlatformObject::Init()
{
	mTag = PLATFORM;
	mTransform.SetWorldPosition({600.f, 600.f});
	mTransform.SetLocalScale({ 200.f, 200.f });
	AddComponent<Rigidbody>(0, false, 10.f, 0, DYNAMIC);
	AddComponent<BoxCollider>();
	AddComponent<Platform>();
	GetComponent<Platform>()->SetGrab(true);
	GetComponent<Platform>()->SetHit(true);
}
