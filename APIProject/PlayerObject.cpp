#include "pch.h"
#include "PlayerObject.h"

#include "BoxCollider.h"

void PlayerObject::Init()
{
	AddComponent<Rigidbody>();
	AddComponent<BoxCollider>();
}
